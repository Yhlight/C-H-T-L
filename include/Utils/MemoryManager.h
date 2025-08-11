#ifndef CHTL_MEMORY_MANAGER_H
#define CHTL_MEMORY_MANAGER_H

#include <memory>
#include <vector>
#include <unordered_map>
#include <functional>
#include <atomic>
#include <mutex>

namespace chtl {

/**
 * 内存管理器 - 优化CHTL编译器的内存使用
 */
class MemoryManager {
public:
    // 内存统计信息
    struct MemoryStats {
        size_t totalAllocated = 0;      // 总分配内存
        size_t currentUsage = 0;        // 当前使用内存
        size_t peakUsage = 0;           // 峰值内存使用
        size_t allocationCount = 0;     // 分配次数
        size_t deallocationCount = 0;   // 释放次数
        size_t pooledAllocations = 0;   // 池化分配次数
        size_t directAllocations = 0;   // 直接分配次数
    };
    
    // 单例模式
    static MemoryManager& getInstance();
    
    // 禁用拷贝
    MemoryManager(const MemoryManager&) = delete;
    MemoryManager& operator=(const MemoryManager&) = delete;
    
    /**
     * 分配内存
     * @param size 要分配的大小
     * @return 分配的内存指针
     */
    void* allocate(size_t size);
    
    /**
     * 释放内存
     * @param ptr 要释放的指针
     * @param size 内存大小
     */
    void deallocate(void* ptr, size_t size);
    
    /**
     * 获取内存统计信息
     */
    MemoryStats getStats() const;
    
    /**
     * 重置统计信息
     */
    void resetStats();
    
    /**
     * 强制垃圾回收
     */
    void collectGarbage();
    
    /**
     * 设置内存限制
     * @param limit 内存限制（字节）
     */
    void setMemoryLimit(size_t limit);
    
    /**
     * 获取内存使用报告
     */
    std::string getMemoryReport() const;
    
private:
    MemoryManager();
    ~MemoryManager();
    
    // 内存池
    class MemoryPool {
    public:
        explicit MemoryPool(size_t blockSize);
        ~MemoryPool();
        
        void* allocate();
        void deallocate(void* ptr);
        bool contains(void* ptr) const;
        size_t getBlockSize() const { return blockSize_; }
        size_t getTotalMemory() const;
        void reset();
        
    private:
        struct Block {
            Block* next;
        };
        
        size_t blockSize_;
        std::vector<std::unique_ptr<char[]>> chunks_;
        Block* freeList_ = nullptr;
        size_t blocksPerChunk_;
        static constexpr size_t CHUNK_SIZE = 64 * 1024; // 64KB
    };
    
    // 不同大小的内存池
    std::vector<std::unique_ptr<MemoryPool>> pools_;
    static constexpr size_t POOL_SIZES[] = {
        16, 32, 64, 128, 256, 512, 1024, 2048, 4096
    };
    
    // 统计信息
    mutable std::mutex statsMutex_;
    MemoryStats stats_;
    std::atomic<size_t> memoryLimit_{0};
    
    // 查找合适的内存池
    MemoryPool* findPool(size_t size);
    
    // 更新统计信息
    void updateStats(size_t allocated, bool isAllocation);
};

/**
 * 智能指针删除器 - 使用内存管理器
 */
template<typename T>
struct MemoryManagerDeleter {
    void operator()(T* ptr) {
        ptr->~T();
        MemoryManager::getInstance().deallocate(ptr, sizeof(T));
    }
};

/**
 * 创建使用内存管理器的对象
 */
template<typename T, typename... Args>
std::unique_ptr<T, MemoryManagerDeleter<T>> makeManaged(Args&&... args) {
    void* mem = MemoryManager::getInstance().allocate(sizeof(T));
    T* obj = new(mem) T(std::forward<Args>(args)...);
    return std::unique_ptr<T, MemoryManagerDeleter<T>>(obj);
}

/**
 * 字符串池 - 减少字符串重复
 */
class StringPool {
public:
    static StringPool& getInstance();
    
    /**
     * 获取或创建字符串
     * @param str 字符串
     * @return 池化的字符串引用
     */
    const std::string& intern(const std::string& str);
    
    /**
     * 清空字符串池
     */
    void clear();
    
    /**
     * 获取池大小
     */
    size_t size() const { return pool_.size(); }
    
    /**
     * 获取内存使用
     */
    size_t getMemoryUsage() const;
    
private:
    StringPool() = default;
    mutable std::mutex mutex_;
    std::unordered_map<std::string, std::unique_ptr<std::string>> pool_;
};

/**
 * 对象池 - 复用频繁创建的对象
 */
template<typename T>
class ObjectPool {
public:
    ObjectPool() = default;
    ~ObjectPool() = default;
    
    /**
     * 获取对象
     */
    std::shared_ptr<T> acquire() {
        std::lock_guard<std::mutex> lock(mutex_);
        
        if (!available_.empty()) {
            auto obj = available_.back();
            available_.pop_back();
            return obj;
        }
        
        return std::make_shared<T>();
    }
    
    /**
     * 归还对象
     */
    void release(std::shared_ptr<T> obj) {
        if (!obj) return;
        
        std::lock_guard<std::mutex> lock(mutex_);
        
        // 重置对象状态
        if constexpr (std::is_same_v<T, Node>) {
            obj->reset();
        }
        
        available_.push_back(obj);
    }
    
    /**
     * 清空对象池
     */
    void clear() {
        std::lock_guard<std::mutex> lock(mutex_);
        available_.clear();
    }
    
    /**
     * 获取池大小
     */
    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return available_.size();
    }
    
private:
    mutable std::mutex mutex_;
    std::vector<std::shared_ptr<T>> available_;
};

} // namespace chtl

#endif // CHTL_MEMORY_MANAGER_H