#pragma once

#include "util.hpp"

namespace edgs {

  /**
   * struct pair - basic pair class
   *
   * @tparam T1
   * @tparam T2
   */
  template <typename T1, typename T2>
  struct pair{

    pair() = default;
    pair(const T1& f, const T2& s) : first{f}, second{s} {}
    pair(const T1&& f, const T2&& s) : first{move(f)}, second{move(s)} {}

    pair(const pair& rhs) : first{rhs.first}, second{rhs.second} {}
    pair(const pair&& rhs) 
      : first{move(rhs.first)}, second{move(rhs.second)} {}

    pair& operator=(const pair& rhs) = default;

    pair& operator=(const pair&& rhs) {
      first = move(rhs.first);
      second = move(rhs.second);
      return *this;
    }

    bool operator==(const pair& rhs) const = default;
    bool operator!=(const pair& rhs) const = default;

    void swap(pair& p){ edgs::swap(*this, p); }

    T1 first{};
    T2 second{};

  };

  template <typename T1, typename T2>
  pair<T1, T2> make_pair(T1&& f, T2&& s)
  {
    return pair<T1, T2>(f, s);
  }
}
