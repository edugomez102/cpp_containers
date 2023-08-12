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
   * struct vector - dynamic contiguous array
   *
   * @tparam T type of container
   */
  template <typename T>
  struct vector{

    using iterator = cont_it<T>;
    using vector_it = vector<T>::iterator;

    vector() 
      : al_{allocator<T>{}}
    {
      create_storage(0);
    }

    vector(size_t l) 
      : al_{allocator<T>{}}
    {
      create_storage(l);
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

    vector(const vector& v) {
      for (auto& i : v) push_back(i);
    }

    vector& operator=(const vector& v) {
      clear();
      for (auto& i : v) push_back(i);
      return *this;
    }

    // vector(const vector&&) = delete;
    // vector& operator=(const vector&&) = delete;

    ~vector() 
    {
      clear();
      al_.deallocate(start_, index_);
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

    void clear()
    {
      al_.destroy(start_);
      index_ = 0;
    }

    vector_it insert(vector_it position, T&& value)
    {
      return insert_impl(position, std::forward<T>(value));
    }

    vector_it insert(vector_it position, const T& value)
    {
      return insert_impl(position, value);
    }

    // vector_it  emplace

    // resize

    void push_back(const T& value)
    {
      if (index_ >= capacity_) {
        if(empty()) {
          create_storage(1);
          reallocate(1);
        }
        else {
          reallocate();
        }
      }
      start_[index_++] = value;
    }

    void pop_back() 
    {
      if (index_ > 0) {
        al_.destroy(start_);
        index_--;
      }
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
      if (index_ <= i) throw std::out_of_range("size is " + index_);
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

    vector_it begin() { return vector_it::begin(start_);        }
    vector_it end()   { return vector_it::end(start_ + index_); }

    const vector_it begin() const { return vector_it::begin(start_);        }
    const vector_it end()   const { return vector_it::end(start_ + index_); }

  private:

    void reallocate(const size_t newsize)
    {
      T* aux = al_.allocate(newsize);

      edgs::copy(start_, start_ + capacity_, aux);
      // allocator<T>::deallocate(start_);
      al_.deallocate(start_, 0);

      start_    = aux;
      capacity_ = newsize;
    }

    void reallocate() { reallocate(capacity_ * 2); }

    void create_storage(const size_t n)
    {
      start_ = al_.allocate(n);
      index_ = 0;
      capacity_ = n;
    }

    vector_it insert_impl(vector_it position, const T& value)
    {
      if(position != start_ + index_)
      {
        const size_t ii = position.base() - start_;
        if (index_ + ii >= capacity_) reallocate();

        edgs::shift_right(start_ + ii, start_ + capacity_ , 1);
        start_[ii] = value;
        ++index_;
        return vector_it::begin(start_ + ii);
      }
      else
      {
        push_back(value);
        return end() - 1;
      }
    }

  private:

    T* start_{nullptr};
    size_t index_{0};
    size_t capacity_{0};

    allocator<T> al_{};

  };
}
