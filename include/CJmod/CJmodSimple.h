#ifndef CHTL_CJMOD_SIMPLE_H
#define CHTL_CJMOD_SIMPLE_H

#include <string>
#include <vector>

namespace chtl {
namespace cjmod {

// 前向声明
class CJmodLoaderImpl;

class CJmodLoader {
private:
    CJmodLoaderImpl* impl_;
    CJmodLoader();
    
public:
    ~CJmodLoader();
    static CJmodLoader& getInstance();
    void initializeBuiltins();
    bool loadModule(const std::string& name);
    bool isModuleLoaded(const std::string& name) const;
};

class CHTLJSProcessor {
public:
    static CHTLJSProcessor& getInstance();
    std::string processJavaScript(const std::string& jsCode, 
                                 const std::vector<std::string>& modules);
    std::string getCombinedRuntime(const std::vector<std::string>& modules);
};

} // namespace cjmod
} // namespace chtl

#endif // CHTL_CJMOD_SIMPLE_H