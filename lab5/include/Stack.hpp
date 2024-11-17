#ifndef STACK_HPP
#define STACK_HPP

#include <memory_resource>
#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <utility>

template <typename T>
class Stack {
public:
    using allocator_type = std::pmr::polymorphic_allocator<T>;

    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;

        Iterator(pointer ptr) : ptr_(ptr) {}

        reference operator*() const { return *ptr_; }
        pointer operator->() { return ptr_; }

        Iterator& operator++() { 
            ++ptr_; 
            return *this; 
        }

        Iterator operator++(int) { 
            Iterator tmp = *this; 
            ++(*this); 
            return tmp; 
        }

        bool operator==(const Iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const Iterator& other) const { return ptr_ != other.ptr_; }

    private:
        pointer ptr_;
    };

    explicit Stack(allocator_type alloc = allocator_type()) 
        : allocator_(alloc), size_(0), capacity_(1) {
        data_ = allocator_.allocate(capacity_);
    }

    ~Stack() {
        for (size_t i = 0; i < size_; ++i) {
            data_[i].~T();
        }
        allocator_.deallocate(data_, capacity_);
    }

    void push(const T& value) {
        if (size_ == capacity_) {
            resize(capacity_ * 2);
        }
        new (&data_[size_]) T(value);
        ++size_;
    }

    void push(T&& value) {
        if (size_ == capacity_) {
            resize(capacity_ * 2);
        }
        new (&data_[size_]) T(std::move(value));
        ++size_;
    }

    void pop() {
        if (size_ == 0) {
            throw std::out_of_range("Stack<>::pop(): empty stack");
        }
        --size_;
        data_[size_].~T();
    }

    T& top() {
        if (size_ == 0) {
            throw std::out_of_range("Stack<>::top(): empty stack");
        }
        return data_[size_ - 1];
    }

    const T& top() const {
        if (size_ == 0) {
            throw std::out_of_range("Stack<>::top() const: empty stack");
        }
        return data_[size_ - 1];
    }

    bool empty() const { return size_ == 0; }

    size_t size() const { return size_; }

    Iterator begin() { return Iterator(data_); }
    Iterator end() { return Iterator(data_ + size_); }

private:
    allocator_type allocator_;
    T* data_;
    size_t size_;
    size_t capacity_;

    void resize(size_t new_capacity) {
        T* new_data = allocator_.allocate(new_capacity);
        for (size_t i = 0; i < size_; ++i) {
            new (&new_data[i]) T(std::move(data_[i]));
            data_[i].~T();
        }
        allocator_.deallocate(data_, capacity_);
        data_ = new_data;
        capacity_ = new_capacity;
    }
};

#endif
