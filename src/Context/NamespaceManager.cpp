#include "Context/NamespaceManager.h"
#include "Node/Custom.h"
#include "Node/Template.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>

namespace chtl {

NamespaceManager::NamespaceManager() {
    // 创建根命名空间（全局）
    root_ = std::make_shared<NamespaceDetail>();
    root_->name = "";
    root_->fullPath = "";
    namespaceCache_[""] = root_;
}

bool NamespaceManager::registerNamespace(std::shared_ptr<Namespace> ns, const std::string& parentPath) {
    if (!ns) return false;
    
    std::string nsName = ns->getName();
    if (nsName.empty()) return false;
    
    // 解析父路径
    std::string fullPath = parentPath.empty() ? nsName : parentPath + "." + nsName;
    
    // 查找或创建命名空间
    auto nsInfo = findOrCreateNamespace(fullPath);
    if (!nsInfo) return false;
    
    // 设置命名空间节点
    nsInfo->node = ns;
    
    // 如果是同名命名空间，记录合并
    if (!nsInfo->mergedFrom.empty() || nsInfo->members.size() > 0) {
        nsInfo->mergedFrom.push_back(fullPath);
    }
    
    // 设置命名空间路径信息
    ns->setNamespacePath(splitPath(fullPath));
    
    return true;
}

bool NamespaceManager::registerMember(const std::string& namespacePath, 
                                     const std::string& memberName,
                                     NodeType type,
                                     std::shared_ptr<Node> node) {
    if (memberName.empty() || !node) return false;
    
    // 查找命名空间
    auto nsInfo = findNamespace(namespacePath);
    if (!nsInfo) {
        // 如果命名空间不存在，创建它
        nsInfo = findOrCreateNamespace(namespacePath);
    }
    
    // 检查成员是否已存在
    auto it = nsInfo->members.find(memberName);
    if (it != nsInfo->members.end()) {
        // 成员冲突
        return false;
    }
    
    // 创建成员信息
    NamespaceMember member;
    member.name = memberName;
    member.type = type;
    member.node = node;
    member.fullPath = namespacePath.empty() ? memberName : namespacePath + "." + memberName;
    
    nsInfo->members[memberName] = member;
    return true;
}

std::shared_ptr<NamespaceDetail> NamespaceManager::findNamespace(const std::string& path) {
    // 快速缓存查找
    auto it = namespaceCache_.find(path);
    if (it != namespaceCache_.end()) {
        return it->second;
    }
    
    // 分割路径并逐级查找
    auto parts = splitPath(path);
    auto current = root_;
    
    for (const auto& part : parts) {
        auto childIt = current->children.find(part);
        if (childIt == current->children.end()) {
            return nullptr;
        }
        current = childIt->second;
    }
    
    // 缓存结果
    namespaceCache_[path] = current;
    return current;
}

std::shared_ptr<Node> NamespaceManager::findMember(const std::string& namespacePath, 
                                                   const std::string& memberName) {
    auto nsInfo = findNamespace(namespacePath);
    if (!nsInfo) return nullptr;
    
    auto it = nsInfo->members.find(memberName);
    if (it == nsInfo->members.end()) {
        return nullptr;
    }
    
    return it->second.node;
}

std::pair<std::string, std::string> NamespaceManager::parseMemberPath(const std::string& fullPath) {
    size_t lastDot = fullPath.rfind('.');
    if (lastDot == std::string::npos) {
        // 没有命名空间，只有成员名
        return {"", fullPath};
    }
    
    return {fullPath.substr(0, lastDot), fullPath.substr(lastDot + 1)};
}

bool NamespaceManager::mergeNamespace(const std::string& path, std::shared_ptr<Namespace> ns) {
    auto nsInfo = findNamespace(path);
    if (!nsInfo) {
        // 第一次创建
        return registerNamespace(ns, path.substr(0, path.rfind('.')));
    }
    
    // 记录合并来源
    nsInfo->mergedFrom.push_back(path);
    
    // 合并子节点
    for (const auto& child : ns->getChildren()) {
        if (child->getType() == NodeType::NAMESPACE) {
            // 递归合并子命名空间
            auto childNs = std::static_pointer_cast<Namespace>(child);
            mergeNamespace(path + "." + childNs->getName(), childNs);
        } else {
            // 注册成员
            std::string memberName;
            
            // 根据节点类型获取名称
            if (child->getType() == NodeType::CUSTOM) {
                auto custom = std::static_pointer_cast<Custom>(child);
                memberName = custom->getCustomName();
            } else if (child->getType() == NodeType::TEMPLATE) {
                auto tmpl = std::static_pointer_cast<Template>(child);
                memberName = tmpl->getTemplateName();
            } else {
                memberName = child->getTagName();
            }
            
            if (!memberName.empty()) {
                registerMember(path, memberName, child->getType(), child);
            }
        }
    }
    
    return true;
}

std::vector<NamespaceConflict> NamespaceManager::detectConflicts() {
    std::vector<NamespaceConflict> conflicts;
    
    // 检查每个命名空间的成员冲突
    std::function<void(std::shared_ptr<NamespaceDetail>)> checkNamespace;
    checkNamespace = [&](std::shared_ptr<NamespaceDetail> nsInfo) {
        // 检查成员冲突（这里简化了，实际应该检查合并时的冲突）
        if (nsInfo->mergedFrom.size() > 1) {
            // 这个命名空间被多次定义
            for (const auto& [memberName, member] : nsInfo->members) {
                NamespaceConflict conflict;
                conflict.memberName = memberName;
                conflict.namespacePath = nsInfo->fullPath;
                conflict.sources = nsInfo->mergedFrom;
                conflict.description = "Member '" + memberName + 
                    "' in namespace '" + nsInfo->fullPath + 
                    "' may have conflicts from multiple sources";
                conflicts.push_back(conflict);
            }
        }
        
        // 递归检查子命名空间
        for (const auto& [childName, childInfo] : nsInfo->children) {
            checkNamespace(childInfo);
        }
    };
    
    checkNamespace(root_);
    return conflicts;
}

std::string NamespaceManager::resolveRelativePath(const std::string& relativePath) {
    if (currentNamespace_.empty() || relativePath.empty()) {
        return relativePath;
    }
    
    // 如果是绝对路径（以.开头），去掉前导点
    if (relativePath[0] == '.') {
        return relativePath.substr(1);
    }
    
    // 否则相对于当前命名空间
    return currentNamespace_ + "." + relativePath;
}

void NamespaceManager::printNamespaceTree() const {
    std::cout << "Namespace Tree:\n";
    std::cout << "===============\n";
    printNamespaceInfo(root_, 0);
}

std::shared_ptr<NamespaceDetail> NamespaceManager::createNamespaceInfo(const std::string& name,
                                                                      const std::string& parentPath) {
    auto info = std::make_shared<NamespaceDetail>();
    info->name = name;
    info->parentPath = parentPath;
    info->fullPath = parentPath.empty() ? name : parentPath + "." + name;
    return info;
}

std::shared_ptr<NamespaceDetail> NamespaceManager::findOrCreateNamespace(const std::string& path) {
    if (path.empty()) return root_;
    
    // 检查缓存
    auto it = namespaceCache_.find(path);
    if (it != namespaceCache_.end()) {
        return it->second;
    }
    
    // 分割路径
    auto parts = splitPath(path);
    auto current = root_;
    std::string currentPath;
    
    for (const auto& part : parts) {
        currentPath = currentPath.empty() ? part : currentPath + "." + part;
        
        auto childIt = current->children.find(part);
        if (childIt == current->children.end()) {
            // 创建新的命名空间
            auto newNs = createNamespaceInfo(part, current->fullPath);
            current->children[part] = newNs;
            namespaceCache_[currentPath] = newNs;
            current = newNs;
        } else {
            current = childIt->second;
        }
    }
    
    return current;
}

std::vector<std::string> NamespaceManager::splitPath(const std::string& path) {
    std::vector<std::string> parts;
    if (path.empty()) return parts;
    
    std::stringstream ss(path);
    std::string part;
    
    while (std::getline(ss, part, '.')) {
        if (!part.empty()) {
            parts.push_back(part);
        }
    }
    
    return parts;
}

std::string NamespaceManager::joinPath(const std::vector<std::string>& parts) {
    if (parts.empty()) return "";
    
    std::string result = parts[0];
    for (size_t i = 1; i < parts.size(); ++i) {
        result += "." + parts[i];
    }
    
    return result;
}

void NamespaceManager::printNamespaceInfo(std::shared_ptr<NamespaceDetail> info, int depth) const {
    std::string indent(depth * 2, ' ');
    
    if (!info->name.empty()) {
        std::cout << indent << info->name;
        if (!info->mergedFrom.empty()) {
            std::cout << " (merged from " << info->mergedFrom.size() << " sources)";
        }
        std::cout << ":\n";
    }
    
    // 打印成员
    for (const auto& [memberName, member] : info->members) {
        std::cout << indent << "  - " << memberName 
                  << " (" << static_cast<int>(member.type) << ")\n";
    }
    
    // 递归打印子命名空间
    for (const auto& [childName, childInfo] : info->children) {
        printNamespaceInfo(childInfo, depth + 1);
    }
}

} // namespace chtl