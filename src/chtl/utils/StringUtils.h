#ifndef CHTL_STRING_UTILS_H
#define CHTL_STRING_UTILS_H

#include <string>
#include <string_view>
#include <vector>
#include <algorithm>
#include <sstream>
#include <charconv>
#include <optional>

namespace chtl {
namespace utils {

// 字符串视图（C++17）
using StringView = std::string_view;

// 字符串拼接优化器
class StringBuilder {
public:
    StringBuilder() {
        buffer_.reserve(256);  // 预分配空间
    }
    
    explicit StringBuilder(size_t reserve) {
        buffer_.reserve(reserve);
    }
    
    StringBuilder& append(StringView str) {
        buffer_.append(str);
        return *this;
    }
    
    StringBuilder& append(char c) {
        buffer_.push_back(c);
        return *this;
    }
    
    StringBuilder& append(const char* str) {
        buffer_.append(str);
        return *this;
    }
    
    template<typename T>
    StringBuilder& append(T value) {
        if constexpr (std::is_integral_v<T>) {
            char buf[32];
            auto [ptr, ec] = std::to_chars(buf, buf + sizeof(buf), value);
            if (ec == std::errc()) {
                buffer_.append(buf, ptr - buf);
            }
        } else {
            buffer_.append(std::to_string(value));
        }
        return *this;
    }
    
    StringBuilder& operator<<(StringView str) {
        return append(str);
    }
    
    template<typename T>
    StringBuilder& operator<<(T&& value) {
        return append(std::forward<T>(value));
    }
    
    std::string toString() const {
        return buffer_;
    }
    
    std::string&& moveString() {
        return std::move(buffer_);
    }
    
    void clear() {
        buffer_.clear();
    }
    
    size_t size() const {
        return buffer_.size();
    }
    
    void reserve(size_t capacity) {
        buffer_.reserve(capacity);
    }
    
private:
    std::string buffer_;
};

// 字符串工具函数
class StringUtils {
public:
    // 去除首尾空白
    static StringView trim(StringView str) {
        auto start = str.find_first_not_of(" \t\n\r");
        if (start == StringView::npos) return "";
        
        auto end = str.find_last_not_of(" \t\n\r");
        return str.substr(start, end - start + 1);
    }
    
    // 分割字符串
    static std::vector<StringView> split(StringView str, char delimiter) {
        std::vector<StringView> result;
        size_t start = 0;
        
        while (start < str.size()) {
            auto pos = str.find(delimiter, start);
            if (pos == StringView::npos) {
                result.push_back(str.substr(start));
                break;
            }
            result.push_back(str.substr(start, pos - start));
            start = pos + 1;
        }
        
        return result;
    }
    
    // 替换字符串（返回新字符串）
    static std::string replace(StringView str, StringView from, StringView to) {
        std::string result;
        result.reserve(str.size());
        
        size_t start = 0;
        while (start < str.size()) {
            auto pos = str.find(from, start);
            if (pos == StringView::npos) {
                result.append(str.substr(start));
                break;
            }
            result.append(str.substr(start, pos - start));
            result.append(to);
            start = pos + from.size();
        }
        
        return result;
    }
    
    // 快速判断前缀
    static bool startsWith(StringView str, StringView prefix) {
        return str.size() >= prefix.size() && 
               str.substr(0, prefix.size()) == prefix;
    }
    
    // 快速判断后缀
    static bool endsWith(StringView str, StringView suffix) {
        return str.size() >= suffix.size() && 
               str.substr(str.size() - suffix.size()) == suffix;
    }
    
    // 转换为小写
    static std::string toLower(StringView str) {
        std::string result(str);
        std::transform(result.begin(), result.end(), result.begin(),
                      [](char c) { return std::tolower(c); });
        return result;
    }
    
    // 转换为大写
    static std::string toUpper(StringView str) {
        std::string result(str);
        std::transform(result.begin(), result.end(), result.begin(),
                      [](char c) { return std::toupper(c); });
        return result;
    }
    
    // 快速数字转换
    template<typename T>
    static std::optional<T> toNumber(StringView str) {
        T value;
        auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), value);
        if (ec == std::errc() && ptr == str.data() + str.size()) {
            return value;
        }
        return std::nullopt;
    }
    
    // 连接字符串
    template<typename Container>
    static std::string join(const Container& container, StringView delimiter) {
        StringBuilder builder;
        bool first = true;
        
        for (const auto& item : container) {
            if (!first) {
                builder.append(delimiter);
            }
            builder.append(item);
            first = false;
        }
        
        return builder.moveString();
    }
    
    // HTML转义
    static std::string escapeHtml(StringView str) {
        StringBuilder builder(str.size() * 1.2);  // 预估大小
        
        for (char c : str) {
            switch (c) {
                case '&':  builder.append("&amp;"); break;
                case '<':  builder.append("&lt;"); break;
                case '>':  builder.append("&gt;"); break;
                case '"':  builder.append("&quot;"); break;
                case '\'': builder.append("&#39;"); break;
                default:   builder.append(c); break;
            }
        }
        
        return builder.moveString();
    }
    
    // 判断是否为有效标识符
    static bool isValidIdentifier(StringView str) {
        if (str.empty()) return false;
        
        // 首字符必须是字母或下划线
        if (!std::isalpha(str[0]) && str[0] != '_') {
            return false;
        }
        
        // 其余字符可以是字母、数字或下划线
        return std::all_of(str.begin() + 1, str.end(),
                          [](char c) { 
                              return std::isalnum(c) || c == '_'; 
                          });
    }
};

// 字符串字面量哈希（编译期）
constexpr size_t hash(const char* str) {
    size_t hash = 5381;
    while (*str) {
        hash = ((hash << 5) + hash) + *str++;
    }
    return hash;
}

// 用户定义字面量
inline size_t operator""_hash(const char* str, size_t) {
    return hash(str);
}

// 字符串内部化（字符串池）
class StringPool {
public:
    static StringPool& getInstance() {
        static StringPool instance;
        return instance;
    }
    
    StringView intern(StringView str) {
        auto it = pool_.find(std::string(str));
        if (it != pool_.end()) {
            return *it;
        }
        
        auto [inserted, success] = pool_.insert(std::string(str));
        return *inserted;
    }
    
    void clear() {
        pool_.clear();
    }
    
    size_t size() const {
        return pool_.size();
    }
    
private:
    StringPool() = default;
    std::unordered_set<std::string> pool_;
};

} // namespace utils
} // namespace chtl

#endif // CHTL_STRING_UTILS_H