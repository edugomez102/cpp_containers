#pragma once 

#include "util.hpp"
#include "contiguous_iterator.hpp"

#include <initializer_list>
#include <stdexcept>

namespace edgs {

  /**
   * struct array - static contiguous array
   *
   * Does NOT support zero-sized arrays
   *
   * @tparam T container type
   * @tparam S array fixed size
   */
  template <typename T, size_t S>
  struct array {

    array() = default;
    array(const T data[S]) { edgs::copy(data, data + S, buf_); }

    array(const std::initializer_list<T>& c)
    {
      edgs::fill_from_initializer_list(c, buf_);
    }

    array(const array& a)
    {
      edgs::copy(
          const_cast<T*>(a.data()), 
          const_cast<T*>(a.data()) + S, 
          buf_);
    }

    array& operator=(const array& v) = delete;

    //--------------------------------------------------------------------
    // Capacity
    //--------------------------------------------------------------------

    [[nodiscard]] constexpr size_t size()  const noexcept { return S; }
    [[nodiscard]] constexpr size_t empty() const noexcept { return S == 0; }

    //--------------------------------------------------------------------
    // Access
    //--------------------------------------------------------------------

    // undefined behaviour if out of range
    [[nodiscard]] T& operator[](const size_t rhs) noexcept { return buf_[rhs]; }

    [[nodiscard]] const T& operator[](const size_t rhs) const noexcept
    {
      return const_cast<array<T, S>*>(this)->operator[](rhs);
    }

    T& at(const size_t i)
    {
      if (S <= i) throw std::out_of_range("size is " + S);
        return buf_[i];
    }

    const T& at(const size_t i) const 
    { 
      return const_cast<array<T, S>*>(this)->at(i);
    }

    T* data() { return buf_; }
    const T* data() const { return buf_; }

    //--------------------------------------------------------------------
    // Iterators
    //--------------------------------------------------------------------

    using iterator = cont_it<T>;
    using array_it = array<T, S>::iterator;

    array_it begin() { return iterator(buf_);   }
    array_it end()   { return iterator(buf_ + S);   }

    // TODO: const iterator
    // const array_it begin() const { return iterator(buf_);   }
    // const array_it end()   const { return iterator(buf_ + S);   }

  private:

    T buf_[S]{0};
  };
}
