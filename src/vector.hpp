#pragma once 

#include "util.hpp"

#include <chrono>
#include <cstdlib>
#include <initializer_list>

namespace edgs{

  template <typename T>
  struct vector{

    // default vector with size 1
    vector() 
    {
      start_ = new T[capacity_];
    }

    vector(size_t l, T value)
      : index_{l}
      , capacity_{l}
    {
      start_ = new T[capacity_];
      edgs::fill(start_, start_ + capacity_, value);
    }

    vector(const std::initializer_list<T>& c)
    {
      start_ = new T[capacity_];
      edgs::fill_from_initializer_list(c, start_);
    }

    ~vector() 
    {
      delete[] start_;
    }

    //--------------------------------------------------------------------
    // Capacity
    //--------------------------------------------------------------------

    size_t size() const     { return index_; }
    size_t capacity() const { return capacity_; }

    bool empty() const { return index_ == 0; }

    // reserve

    //--------------------------------------------------------------------
    // Modifiers
    //--------------------------------------------------------------------

    // clear
    // insert(size_t position, const T& value)
    // emplace
    // resize

    void push_back(const T& value)
    {
      if (index_ >= capacity_)
        reallocate(capacity_ * 2);
      insert_element(value);
    }

    void pop_back() 
    {
      // TODO should also delete unused resources ~T()

      if (index_ > 0)
        index_--;
    }

    //--------------------------------------------------------------------
    // Access
    //--------------------------------------------------------------------

    [[nodiscard]] T& operator[](const size_t rhs) noexcept {return start_[rhs];}

    [[nodiscard]] const T& operator[](const size_t rhs) const noexcept
    {
      return start_[rhs];
    }

    T& at(const size_t i)
    {
      if (i < 0 || index_ <= i) throw std::out_of_range("size is " + index_);
        return start_[i];
    }

    const T& at(const size_t i) const 
    { 
      return const_cast<vector<T>*>(this)->at(i);
    }

    T* data() { return start_; }
    const T* data() const { return start_; }

    //--------------------------------------------------------------------
    // Iterators
    //--------------------------------------------------------------------

    auto begin() const { return std::begin(start_); } 
    auto end()   const { return std::end(start_); }


  private:

    void reallocate(size_t newsize)
    {
      T* aux = new T[newsize];
      edgs::copy(start_, start_ + capacity_, aux);
      delete[] start_;

      start_    = aux;
      capacity_ = newsize;
    }

    void insert_element(const T& value)
    {
      start_[index_++] = value;
    }

    T* start_{nullptr};
    size_t index_{0};
    size_t capacity_{1};

  };
}
