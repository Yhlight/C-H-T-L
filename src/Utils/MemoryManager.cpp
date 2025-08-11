#include "Utils/MemoryManager.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <algorithm>

namespace chtl {

// MemoryPool 实现
MemoryManager::MemoryPool::MemoryPool(size_t blockSize) 
    : blockSize_(blockSize) {
    blocksPerChunk_ = CHUNK_SIZE / blockSize_;
    if (blocksPerChunk_ == 0) {
        blocksPerChunk_ = 1;
    }
}

MemoryManager::MemoryPool::~MemoryPool() {
    // 析构时自动释放所有chunks
}

void* MemoryManager::MemoryPool::allocate() {
    if (!freeList_) {
        // 分配新的chunk
        auto chunk = std::make_unique<char[]>(blocksPerChunk_ * blockSize_);
        char* chunkPtr = chunk.get();
        
        // 初始化free list
        for (size_t i = 0; i < blocksPerChunk_ - 1; ++i) {
            Block* block = reinterpret_cast<Block*>(chunkPtr + i * blockSize_);
            block->next = reinterpret_cast<Block*>(chunkPtr + (i + 1) * blockSize_);
        }
        
        // 最后一个块
        Block* lastBlock = reinterpret_cast<Block*>(chunkPtr + (blocksPerChunk_ - 1) * blockSize_);
        lastBlock->next = nullptr;
        
        freeList_ = reinterpret_cast<Block*>(chunkPtr);
        chunks_.push_back(std::move(chunk));
    }
    
    // 从free list取出一个块
    Block* block = freeList_;
    freeList_ = freeList_->next;
    
    return block;
}

void MemoryManager::MemoryPool::deallocate(void* ptr) {
    if (!ptr) return;
    
    // 将块放回free list
    Block* block = reinterpret_cast<Block*>(ptr);
    block->next = freeList_;
    freeList_ = block;
}

bool MemoryManager::MemoryPool::contains(void* ptr) const {
    for (const auto& chunk : chunks_) {
        char* chunkStart = chunk.get();
        char* chunkEnd = chunkStart + blocksPerChunk_ * blockSize_;
        
        if (ptr >= chunkStart && ptr < chunkEnd) {
            // 检查对齐
            size_t offset = static_cast<char*>(ptr) - chunkStart;
            return offset % blockSize_ == 0;
        }
    }
    return false;
}

size_t MemoryManager::MemoryPool::getTotalMemory() const {
    return chunks_.size() * blocksPerChunk_ * blockSize_;
}

void MemoryManager::MemoryPool::reset() {
    chunks_.clear();
    freeList_ = nullptr;
}

// MemoryManager 静态成员定义
constexpr size_t MemoryManager::POOL_SIZES[];

// MemoryManager 实现
MemoryManager::MemoryManager() {
    // 初始化内存池
    for (size_t poolSize : POOL_SIZES) {
        pools_.push_back(std::make_unique<MemoryPool>(poolSize));
    }
}

MemoryManager::~MemoryManager() {
    // 输出最终的内存统计
    std::cout << getMemoryReport() << std::endl;
}

MemoryManager& MemoryManager::getInstance() {
    static MemoryManager instance;
    return instance;
}

void* MemoryManager::allocate(size_t size) {
    // 检查内存限制
    size_t limit = memoryLimit_.load();
    if (limit > 0 && stats_.currentUsage + size > limit) {
        throw std::bad_alloc();
    }
    
    void* ptr = nullptr;
    
    // 尝试从内存池分配
    MemoryPool* pool = findPool(size);
    if (pool) {
        ptr = pool->allocate();
        updateStats(size, true);
        stats_.pooledAllocations++;
    } else {
        // 大块内存直接分配
        ptr = std::malloc(size);
        if (!ptr) {
            throw std::bad_alloc();
        }
        updateStats(size, true);
        stats_.directAllocations++;
    }
    
    return ptr;
}

void MemoryManager::deallocate(void* ptr, size_t size) {
    if (!ptr) return;
    
    // 尝试归还到内存池
    MemoryPool* pool = findPool(size);
    if (pool && pool->contains(ptr)) {
        pool->deallocate(ptr);
    } else {
        // 直接释放
        std::free(ptr);
    }
    
    updateStats(size, false);
}

MemoryManager::MemoryStats MemoryManager::getStats() const {
    std::lock_guard<std::mutex> lock(statsMutex_);
    return stats_;
}

void MemoryManager::resetStats() {
    std::lock_guard<std::mutex> lock(statsMutex_);
    stats_ = MemoryStats();
}

void MemoryManager::collectGarbage() {
    // 清理内存池中未使用的chunks
    for (auto& pool : pools_) {
        // 这里可以实现更智能的垃圾回收策略
        // 目前只是重置空闲列表
    }
}

void MemoryManager::setMemoryLimit(size_t limit) {
    memoryLimit_.store(limit);
}

std::string MemoryManager::getMemoryReport() const {
    auto stats = getStats();
    std::stringstream report;
    
    report << "=== CHTL Memory Usage Report ===\n\n";
    
    report << "Current Usage: " << std::fixed << std::setprecision(2)
           << (stats.currentUsage / 1024.0 / 1024.0) << " MB\n";
    report << "Peak Usage: " << (stats.peakUsage / 1024.0 / 1024.0) << " MB\n";
    report << "Total Allocated: " << (stats.totalAllocated / 1024.0 / 1024.0) << " MB\n\n";
    
    report << "Allocations: " << stats.allocationCount << "\n";
    report << "Deallocations: " << stats.deallocationCount << "\n";
    report << "Pooled Allocations: " << stats.pooledAllocations << " ("
           << (stats.pooledAllocations * 100.0 / stats.allocationCount) << "%)\n";
    report << "Direct Allocations: " << stats.directAllocations << " ("
           << (stats.directAllocations * 100.0 / stats.allocationCount) << "%)\n\n";
    
    report << "Memory Pool Usage:\n";
    for (size_t i = 0; i < pools_.size(); ++i) {
        report << "  Pool " << POOL_SIZES[i] << " bytes: "
               << (pools_[i]->getTotalMemory() / 1024.0) << " KB\n";
    }
    
    return report.str();
}

MemoryManager::MemoryPool* MemoryManager::findPool(size_t size) {
    // 找到第一个足够大的池
    for (size_t i = 0; i < pools_.size(); ++i) {
        if (POOL_SIZES[i] >= size) {
            return pools_[i].get();
        }
    }
    return nullptr;
}

void MemoryManager::updateStats(size_t size, bool isAllocation) {
    std::lock_guard<std::mutex> lock(statsMutex_);
    
    if (isAllocation) {
        stats_.totalAllocated += size;
        stats_.currentUsage += size;
        stats_.allocationCount++;
        
        if (stats_.currentUsage > stats_.peakUsage) {
            stats_.peakUsage = stats_.currentUsage;
        }
    } else {
        stats_.currentUsage -= std::min(stats_.currentUsage, size);
        stats_.deallocationCount++;
    }
}

// StringPool 实现
StringPool& StringPool::getInstance() {
    static StringPool instance;
    return instance;
}

const std::string& StringPool::intern(const std::string& str) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    auto it = pool_.find(str);
    if (it != pool_.end()) {
        return *it->second;
    }
    
    // 创建新字符串
    auto ptr = std::make_unique<std::string>(str);
    const std::string& ref = *ptr;
    pool_[str] = std::move(ptr);
    
    return ref;
}

void StringPool::clear() {
    std::lock_guard<std::mutex> lock(mutex_);
    pool_.clear();
}

size_t StringPool::getMemoryUsage() const {
    std::lock_guard<std::mutex> lock(mutex_);
    
    size_t usage = 0;
    for (const auto& [key, value] : pool_) {
        usage += key.capacity() + value->capacity() + sizeof(std::string) * 2;
    }
    
    return usage;
}

} // namespace chtl