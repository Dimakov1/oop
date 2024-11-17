#ifndef CUSTOM_MEMORY_RESOURCE_HPP
#define CUSTOM_MEMORY_RESOURCE_HPP

#include <memory_resource>
#include <map>
#include <vector>
#include <mutex>
#include <tuple>

class CustomMemoryResource : public std::pmr::memory_resource {
public:
    CustomMemoryResource() = default;
    ~CustomMemoryResource() override;

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

private:
    mutable std::mutex mtx_;
    std::map<void*, std::pair<std::size_t, std::size_t>> allocated_blocks_;

    std::vector<std::tuple<void*, std::size_t, std::size_t>> free_blocks_;
};

#endif
