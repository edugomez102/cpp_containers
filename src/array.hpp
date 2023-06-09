#pragma once 

#include "util.hpp"
#include "contiguous_iterator.hpp"

#include <initializer_list>
#include <stdexcept>

namespace edgs {

  /**
   * struct array - array container implementation
   * Does NOT support zero-sized arrays
   *
   * @tparam T container type
   * @tparam S array fixed size
   */
  template <typename T, size_t S>
  struct array {

    array() = default;
    array(T data[S]) { edgs::copy(data, data + S, buf_); }

    array(const std::initializer_list<T>& c)
    {
      edgs::fill_from_initializer_list(c, buf_);
    }

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
      if (i < 0 || S <= i) throw std::out_of_range("size is " + S);
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

    array_it begin() { return array_it::begin(buf_);   }
    array_it end()   { return array_it::end(buf_ + S);   }

  private:

    T buf_[S]{0};
  };
}
