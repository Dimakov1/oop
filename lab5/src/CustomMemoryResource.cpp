#include "CustomMemoryResource.hpp"
#include <cstdlib>
#include <iostream>
#include <algorithm>

CustomMemoryResource::~CustomMemoryResource() {
    std::lock_guard<std::mutex> lock(mtx_);
    for (const auto& [ptr, info] : allocated_blocks_) {
        std::free(ptr);
        std::cout << "MemoryResource: Deallocated memory at " << ptr << std::endl;
    }
    allocated_blocks_.clear();

    for (const auto& [ptr, bytes, alignment] : free_blocks_) {
        std::free(ptr);
        std::cout << "MemoryResource: Deallocated free memory at " << ptr << std::endl;
    }
    free_blocks_.clear();
}

void* CustomMemoryResource::do_allocate(std::size_t bytes, std::size_t alignment) {
    std::lock_guard<std::mutex> lock(mtx_);

    std::size_t adjusted_bytes = bytes;
    if (bytes % alignment != 0) {
        adjusted_bytes = bytes + (alignment - (bytes % alignment));
    }

    auto it = std::find_if(free_blocks_.begin(), free_blocks_.end(),
        [&](const std::tuple<void*, std::size_t, std::size_t>& block) {
            return std::get<1>(block) == adjusted_bytes && std::get<2>(block) == alignment;
        });

    if (it != free_blocks_.end()) {
        void* ptr = std::get<0>(*it);
        free_blocks_.erase(it);
        allocated_blocks_[ptr] = { adjusted_bytes, alignment };
        std::cout << "MemoryResource: Reusing memory at " << ptr << std::endl;
        return ptr;
    }

    void* ptr = std::aligned_alloc(alignment, adjusted_bytes);
    if (!ptr) {
        throw std::bad_alloc();
    }
    allocated_blocks_[ptr] = { adjusted_bytes, alignment };
    std::cout << "MemoryResource: Allocated new memory at " << ptr << std::endl;
    return ptr;
}

void CustomMemoryResource::do_deallocate(void* p, std::size_t bytes, std::size_t alignment) {
    std::lock_guard<std::mutex> lock(mtx_);
    auto it = allocated_blocks_.find(p);
    if (it != allocated_blocks_.end()) {
        std::cout << "MemoryResource: Deallocated memory at " << p << std::endl;
        free_blocks_.emplace_back(p, it->second.first, it->second.second);
        allocated_blocks_.erase(it);
    } else {
        std::cerr << "MemoryResource: Attempt to deallocate unknown pointer " << p << std::endl;
    }
}

bool CustomMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}
