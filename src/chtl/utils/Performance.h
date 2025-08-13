#ifndef CHTL_PERFORMANCE_H
#define CHTL_PERFORMANCE_H

#include <chrono>
#include <string>
#include <unordered_map>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <thread>

namespace chtl {
namespace utils {

// 性能计时器
class Timer {
public:
    Timer() : start_(std::chrono::high_resolution_clock::now()) {}
    
    void reset() {
        start_ = std::chrono::high_resolution_clock::now();
    }
    
    double elapsed() const {
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double, std::milli>(end - start_).count();
    }
    
    double elapsedSeconds() const {
        return elapsed() / 1000.0;
    }
    
private:
    std::chrono::high_resolution_clock::time_point start_;
};

// 性能分析器
class Profiler {
public:
    static Profiler& getInstance() {
        static Profiler instance;
        return instance;
    }
    
    // 开始计时
    void begin(const std::string& name) {
        timers_[name] = Timer();
    }
    
    // 结束计时
    void end(const std::string& name) {
        auto it = timers_.find(name);
        if (it != timers_.end()) {
            double duration = it->second.elapsed();
            records_[name].push_back(duration);
            timers_.erase(it);
        }
    }
    
    // 获取平均时间
    double getAverage(const std::string& name) const {
        auto it = records_.find(name);
        if (it == records_.end() || it->second.empty()) {
            return 0.0;
        }
        
        double sum = 0.0;
        for (double d : it->second) {
            sum += d;
        }
        return sum / it->second.size();
    }
    
    // 打印报告
    void report() const {
        std::cout << "\n=== Performance Report ===\n";
        std::cout << std::setw(30) << "Function" 
                  << std::setw(10) << "Calls"
                  << std::setw(15) << "Total (ms)"
                  << std::setw(15) << "Average (ms)"
                  << std::setw(15) << "Min (ms)"
                  << std::setw(15) << "Max (ms)\n";
        std::cout << std::string(90, '-') << "\n";
        
        for (const auto& [name, times] : records_) {
            if (times.empty()) continue;
            
            double total = 0.0;
            double minTime = times[0];
            double maxTime = times[0];
            
            for (double t : times) {
                total += t;
                minTime = std::min(minTime, t);
                maxTime = std::max(maxTime, t);
            }
            
            std::cout << std::setw(30) << name
                      << std::setw(10) << times.size()
                      << std::setw(15) << std::fixed << std::setprecision(2) << total
                      << std::setw(15) << (total / times.size())
                      << std::setw(15) << minTime
                      << std::setw(15) << maxTime << "\n";
        }
    }
    
    // 清除记录
    void clear() {
        timers_.clear();
        records_.clear();
    }
    
private:
    Profiler() = default;
    std::unordered_map<std::string, Timer> timers_;
    std::unordered_map<std::string, std::vector<double>> records_;
};

// RAII性能计时器
class ScopedTimer {
public:
    ScopedTimer(const std::string& name) : name_(name) {
        Profiler::getInstance().begin(name_);
    }
    
    ~ScopedTimer() {
        Profiler::getInstance().end(name_);
    }
    
private:
    std::string name_;
};

// 便捷宏
#define PROFILE(name) \
    chtl::utils::ScopedTimer CHTL_CONCAT(_timer_, __LINE__)(name)

#define PROFILE_FUNC() \
    PROFILE(__FUNCTION__)

// 并行执行辅助
template<typename Iterator, typename Func>
void parallelFor(Iterator begin, Iterator end, Func func, size_t numThreads = 0) {
    if (numThreads == 0) {
        numThreads = std::thread::hardware_concurrency();
    }
    
    size_t totalSize = std::distance(begin, end);
    size_t chunkSize = totalSize / numThreads;
    
    std::vector<std::thread> threads;
    threads.reserve(numThreads);
    
    Iterator chunkBegin = begin;
    for (size_t i = 0; i < numThreads - 1; ++i) {
        Iterator chunkEnd = chunkBegin;
        std::advance(chunkEnd, chunkSize);
        
        threads.emplace_back([chunkBegin, chunkEnd, &func]() {
            for (auto it = chunkBegin; it != chunkEnd; ++it) {
                func(*it);
            }
        });
        
        chunkBegin = chunkEnd;
    }
    
    // 最后一个线程处理剩余的元素
    threads.emplace_back([chunkBegin, end, &func]() {
        for (auto it = chunkBegin; it != end; ++it) {
            func(*it);
        }
    });
    
    // 等待所有线程完成
    for (auto& thread : threads) {
        thread.join();
    }
}

// 缓存装饰器
template<typename Key, typename Value>
class Cache {
public:
    Cache(size_t maxSize = 1000) : maxSize_(maxSize) {}
    
    bool get(const Key& key, Value& value) {
        auto it = cache_.find(key);
        if (it != cache_.end()) {
            // 移到最前面（LRU）
            usage_.erase(it->second.second);
            usage_.push_front(key);
            it->second.second = usage_.begin();
            
            value = it->second.first;
            hits_++;
            return true;
        }
        misses_++;
        return false;
    }
    
    void put(const Key& key, const Value& value) {
        auto it = cache_.find(key);
        
        if (it != cache_.end()) {
            // 更新现有项
            usage_.erase(it->second.second);
            usage_.push_front(key);
            it->second = {value, usage_.begin()};
        } else {
            // 添加新项
            if (cache_.size() >= maxSize_) {
                // 删除最久未使用的项
                cache_.erase(usage_.back());
                usage_.pop_back();
            }
            
            usage_.push_front(key);
            cache_[key] = {value, usage_.begin()};
        }
    }
    
    void clear() {
        cache_.clear();
        usage_.clear();
        hits_ = misses_ = 0;
    }
    
    double getHitRate() const {
        size_t total = hits_ + misses_;
        return total > 0 ? static_cast<double>(hits_) / total : 0.0;
    }
    
private:
    size_t maxSize_;
    std::unordered_map<Key, std::pair<Value, typename std::list<Key>::iterator>> cache_;
    std::list<Key> usage_;
    size_t hits_ = 0;
    size_t misses_ = 0;
};

// 预编译正则表达式缓存
class RegexCache {
public:
    static RegexCache& getInstance() {
        static RegexCache instance;
        return instance;
    }
    
    std::regex& get(const std::string& pattern) {
        auto it = cache_.find(pattern);
        if (it != cache_.end()) {
            return it->second;
        }
        
        // 编译并缓存
        auto [inserted, success] = cache_.emplace(pattern, std::regex(pattern));
        return inserted->second;
    }
    
private:
    RegexCache() = default;
    std::unordered_map<std::string, std::regex> cache_;
};

} // namespace utils
} // namespace chtl

#endif // CHTL_PERFORMANCE_H