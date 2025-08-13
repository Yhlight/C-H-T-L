#ifndef CHTL_MEMORY_H
#define CHTL_MEMORY_H

#include <memory>
#include <vector>
#include <type_traits>
#include <cstddef>

namespace chtl {
namespace utils {

// 内存池分配器
template<typename T, size_t BlockSize = 4096>
class MemoryPool {
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    
    template<typename U>
    struct rebind {
        using other = MemoryPool<U, BlockSize>;
    };
    
    MemoryPool() noexcept {
        currentBlock = nullptr;
        currentSlot = nullptr;
        lastSlot = nullptr;
        freeSlots = nullptr;
    }
    
    ~MemoryPool() noexcept {
        // 释放所有分配的块
        slot_pointer curr = currentBlock;
        while (curr != nullptr) {
            slot_pointer prev = curr->next;
            operator delete(reinterpret_cast<void*>(curr));
            curr = prev;
        }
    }
    
    pointer allocate(size_type n = 1) {
        if (n > 1) {
            // 对于大块分配，使用标准分配器
            return static_cast<pointer>(operator new(n * sizeof(T)));
        }
        
        if (freeSlots != nullptr) {
            // 重用空闲槽位
            pointer result = reinterpret_cast<pointer>(freeSlots);
            freeSlots = freeSlots->next;
            return result;
        } else {
            if (currentSlot >= lastSlot) {
                // 分配新块
                allocateBlock();
            }
            return reinterpret_cast<pointer>(currentSlot++);
        }
    }
    
    void deallocate(pointer p, size_type n = 1) {
        if (n > 1) {
            // 对于大块分配，使用标准释放
            operator delete(p);
            return;
        }
        
        if (p != nullptr) {
            // 将槽位添加到空闲列表
            reinterpret_cast<slot_pointer>(p)->next = freeSlots;
            freeSlots = reinterpret_cast<slot_pointer>(p);
        }
    }
    
private:
    union Slot {
        value_type element;
        Slot* next;
    };
    
    using data_pointer = char*;
    using slot_type = Slot;
    using slot_pointer = Slot*;
    
    slot_pointer currentBlock;
    slot_pointer currentSlot;
    slot_pointer lastSlot;
    slot_pointer freeSlots;
    
    static_assert(BlockSize >= sizeof(slot_type), "BlockSize too small");
    
    void allocateBlock() {
        // 分配新的内存块
        data_pointer newBlock = reinterpret_cast<data_pointer>(
            operator new(BlockSize));
        reinterpret_cast<slot_pointer>(newBlock)->next = currentBlock;
        currentBlock = reinterpret_cast<slot_pointer>(newBlock);
        
        // 设置槽位指针
        data_pointer body = newBlock + sizeof(slot_pointer);
        size_t bodySize = BlockSize - sizeof(slot_pointer);
        currentSlot = reinterpret_cast<slot_pointer>(body);
        lastSlot = reinterpret_cast<slot_pointer>(body + bodySize);
    }
};

// 智能指针别名
template<typename T>
using UniquePtr = std::unique_ptr<T>;

template<typename T>
using SharedPtr = std::shared_ptr<T>;

template<typename T>
using WeakPtr = std::weak_ptr<T>;

// 工厂函数
template<typename T, typename... Args>
UniquePtr<T> makeUnique(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T, typename... Args>
SharedPtr<T> makeShared(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

// 对象池
template<typename T>
class ObjectPool {
public:
    using Deleter = std::function<void(T*)>;
    
    ObjectPool(size_t initialSize = 16) {
        pool_.reserve(initialSize);
    }
    
    template<typename... Args>
    SharedPtr<T> acquire(Args&&... args) {
        T* obj = nullptr;
        
        if (!pool_.empty()) {
            // 从池中获取对象
            obj = pool_.back().release();
            pool_.pop_back();
            
            // 重新初始化对象
            new (obj) T(std::forward<Args>(args)...);
        } else {
            // 创建新对象
            obj = new T(std::forward<Args>(args)...);
        }
        
        // 返回带自定义删除器的智能指针
        return SharedPtr<T>(obj, [this](T* p) { release(p); });
    }
    
    void release(T* obj) {
        if (obj && pool_.size() < maxPoolSize_) {
            obj->~T();  // 调用析构函数
            pool_.emplace_back(obj);
        } else {
            delete obj;
        }
    }
    
    void setMaxPoolSize(size_t size) { maxPoolSize_ = size; }
    size_t getPoolSize() const { return pool_.size(); }
    
private:
    std::vector<UniquePtr<T>> pool_;
    size_t maxPoolSize_ = 100;
};

// RAII守卫
template<typename F>
class ScopeGuard {
public:
    explicit ScopeGuard(F&& f) : f_(std::forward<F>(f)), active_(true) {}
    
    ~ScopeGuard() {
        if (active_) f_();
    }
    
    void dismiss() { active_ = false; }
    
    // 禁止拷贝
    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard& operator=(const ScopeGuard&) = delete;
    
    // 允许移动
    ScopeGuard(ScopeGuard&& other) noexcept
        : f_(std::move(other.f_)), active_(other.active_) {
        other.active_ = false;
    }
    
private:
    F f_;
    bool active_;
};

template<typename F>
ScopeGuard<F> makeScopeGuard(F&& f) {
    return ScopeGuard<F>(std::forward<F>(f));
}

// 便捷宏
#define CHTL_SCOPE_EXIT(code) \
    auto CHTL_CONCAT(_scope_guard_, __LINE__) = \
        chtl::utils::makeScopeGuard([&]() { code; })

#define CHTL_CONCAT(a, b) CHTL_CONCAT_IMPL(a, b)
#define CHTL_CONCAT_IMPL(a, b) a##b

} // namespace utils
} // namespace chtl

#endif // CHTL_MEMORY_H