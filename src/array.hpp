#pragma once 

#include "util.hpp"

#include <initializer_list>
#include <stdexcept>

namespace edgs {

  // No support for zero-sized array

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

    auto begin() const { return std::begin(buf_); } 
    auto end()   const { return std::end(buf_); }


  private:

    T buf_[S]{0};
  };
}
