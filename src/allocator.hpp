#pragma once

#include <cstddef>

namespace edgs {

  template <typename T>
  struct allocator{

    explicit allocator() = default;
    allocator(const allocator&) = delete;
    allocator(const allocator&&) = delete;

    allocator& operator==(const allocator&) = delete;
    allocator& operator==(const allocator&&) = delete;

    T* allocate(const size_t n) {
      return address_ =  static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate() {
      ::operator delete(address_);
    }

    void construct(const size_t n) {
      for (size_t i = 0; i < n ; i++)
        new(address_ + i) T(); // TODO args
    }

    void destroy( const size_t n) {
      for (size_t i = 0; i < n; i++) 
        address_[i].~T();
    };

    static void deallocate(T* dm) {
      ::operator delete(dm);
    }

    constexpr T* address() const { return address_; }

  private:

    T* address_{nullptr};
  };
}
