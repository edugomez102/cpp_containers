#pragma once

#include <cstddef>

namespace edgs {

  /**
   * struct allocator - Basic allocator
   *
   * @tparam T type to allocate
   */
  template <typename T>
  struct allocator{

    using value_type    = T;
    using pointer       = T*;
    using const_pointer = const T*;
    using size_type     = size_t;

    allocator() = default;
    allocator(const allocator&) {}
    allocator(const allocator&&) {}

    pointer allocate(size_type n) {
      return static_cast<pointer>(::operator new(n * sizeof(T)));
    }

    void deallocate(pointer p, size_type /* n */) {
      ::operator delete(p);
    }

    void construct(pointer p, const T& value) {
      new (p) T(value);
    }

    void destroy(pointer p) {
      p->~T();
    }

  };
}
