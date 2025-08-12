#include "Compiler.h"

namespace chtl {

void Compiler::updateStat(const std::string& key, int value) {
    stats_[key] = value;
}

void Compiler::addWarning(const std::string& warning) {
    // 基类实现，子类可以重写
}

void Compiler::setError(const std::string& error) {
    // 基类实现，子类可以重写
}

void Compiler::setOutput(const std::string& output) {
    // 基类实现，子类可以重写
}

void Compiler::setSuccess(bool success) {
    // 基类实现，子类可以重写
}

} // namespace chtl