#pragma once 

#include <cstdio>

#include <initializer_list>
#include <ostream>

namespace edgs {

  template <typename T>
  void copy(T* start, T* end, T* target)
  {
    for (size_t i = 0; i < size_t(end - start); i++)
      target[i] = std::move(start[i]);
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

    Dummy() { printf("Dummy is constructed\n"); }
    Dummy(const int a) 
      : a_{a}
    {
      printf("Dummy is constructed\n");
    }

    ~Dummy() {
      printf("Dummy is destructed\n");
    }

    friend std::ostream& operator<< (std::ostream& o, const Dummy& d)
    {
      return o << "a:" << d.a_ ;
    }

    int   a_{5};
    // float b_{0.f};
  };
}

