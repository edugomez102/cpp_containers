#pragma once 

#include <cstdio>

#include <initializer_list>
#include <ostream>

namespace edgs {

  template <typename T>
  void copy(T* start, T* end, T* target)
  {
    for (size_t i = 0; i < size_t(end - start); i++)
      target[i] = start[i];
  };

  template <typename T>
  void fill(T* start, T* end, const T& value)
  {
    for (size_t i = 0; i < size_t(end - start); i++)
      start[i] = value;
  }

  template <typename T>
  void fill_from_initializer_list(const std::initializer_list<T>& c, T* data)
  {
    T* ptr = data;
    for (const T& i : c) {
      *ptr = i; ptr++;
    }
  }

  struct Dummy{

    Dummy() = default;
    Dummy(const int a, const float b) 
      : a_{a}, b_{b}
    {
      printf("Dummy is constructed\n");
    }

    ~Dummy() {
      printf("Dummy is destructed\n");
    }

    friend std::ostream& operator<< (std::ostream& o, const Dummy& d)
    {
      return o << "a:" << d.a_ << " b:" << d.b_;
    }

    int   a_{0};
    float b_{0.f};
  };
}

