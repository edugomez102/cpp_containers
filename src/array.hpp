
#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <memory>

namespace edgs {

  template <typename T, size_t S>
  struct array {

    array() = default;
    array(T data[S])
    {
      std::copy(data, data + S, buf_);
    }

    array(std::initializer_list<T> c)
    {
      T* ptr = buf_;
      for (const T& i : c) {
        *ptr = i; ptr++;
      }
    }

    constexpr size_t size() const noexcept { return S; }

    // undefined behaviour if out of size
    T& operator[](const size_t rhs) noexcept { return buf_[rhs]; }

    const T& operator[](const size_t rhs) const noexcept
    {
      return const_cast<array<T, S>*>(this)->operator[](rhs);
    }

    [[nodiscard]] T& at(const size_t rhs) const
    {
      // if(buf_[rhs] == 0) {
      //   buf_[rhs] == rhs;
      // }
      // else {
      //   
      // }
    }

    auto begin() const { return std::begin(buf_); } 
    auto end()   const { return std::end(buf_); }

    T* data() { return buf_; }

  private:
    T buf_[S]{0};
  };

}
