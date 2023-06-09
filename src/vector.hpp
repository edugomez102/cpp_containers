#pragma once 

#include "util.hpp"
#include "contiguous_iterator.hpp"
#include "allocator.hpp"

#include <chrono>
#include <cstdlib>
#include <initializer_list>
#include <memory>

namespace edgs{

  /**
   * struct vector - vector container implementation
   *
   * @tparam T type of container
   */
  template <typename T>
  struct vector{

    vector(const vector&)  = delete;
    vector(const vector&&) = delete;
    vector& operator==(const vector&)  = delete;
    vector& operator==(const vector&&) = delete;

    vector() 
      : al_{allocator<T>{}}
    {
      create_storage(0);
    }

    vector(size_t l, T value)
      : al_{allocator<T>{}}
    {
      create_storage(l);
      edgs::fill(start_, start_ + capacity_, value);
      index_ = capacity_;
    }

    vector(const std::initializer_list<T>& c)
      : al_{allocator<T>{}}
    {
      create_storage(c.size());
      edgs::fill_from_initializer_list(c, start_);
      index_ = capacity_;
    }

    ~vector() 
    {
      clear();
      al_.deallocate();
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

    void clear() {
      al_.destroy(index_);
      index_ = 0;
    }
    // insert(size_t position, const T& value)
    // emplace
    // resize

    void push_back(const T& value)
    {
      if (index_ >= capacity_)
      {
        if(empty()) {
          create_storage(1);
          reallocate(1);
        }
        else {
          reallocate(capacity_ * 2);
        }
      }
      insert_element(value);
    }

    void pop_back() 
    {
      if (index_ > 0)
        al_.destroy(index_--);
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

    using iterator = cont_it<T>;
    using vector_it = vector<T>::iterator;

    vector_it begin() { return vector_it::begin(start_);        }
    vector_it end()   { return vector_it::end(start_ + index_); }

  private:

    void reallocate(const size_t newsize)
    {
      T* aux = al_.allocate(newsize);

      edgs::copy(start_, start_ + capacity_, aux);
      allocator<T>::deallocate(start_);

      start_    = aux;
      capacity_ = newsize;
    }

    void insert_element(const T& value)
    {
      start_[index_++] = value;
    }

    void create_storage(const size_t n)
    {
      start_ = al_.allocate(n);
      index_ = 0;
      capacity_ = n;
    }

  private:

    T* start_{nullptr};
    size_t index_{0};
    size_t capacity_{0};

    allocator<T> al_{};

  };
}
