#pragma once 

/**
 * struct cont_it - contiguous iterator 
 *
 * @tparam T type managed by the data structure to iterate
 */
template <typename T>
struct cont_it{

private:

  cont_it(T* start)
    : ptr{start}
  { }

public:

  cont_it& operator++() { ptr++; return *this; }
  cont_it& operator--() { ptr--; return *this;}

  cont_it& operator-(const int rhs) { ptr -= rhs; return *this;}
  cont_it& operator+(const int rhs) { ptr += rhs; return *this;}

  cont_it operator++(int) {
    cont_it tmp = *this;
    ++(*this); return tmp;
  }

  cont_it operator--(int) {
    cont_it tmp = *this;
    --(*this); return tmp;
  }

  const T& operator*()  { return *ptr; }
  cont_it& operator->() { return ptr; }
  cont_it& operator[](unsigned int index) { return ptr + index; }

  bool operator==(const cont_it& rhs) const { return ptr == rhs.ptr; }
  bool operator!=(const cont_it& rhs) const { return ptr != rhs.ptr; }

  bool operator!=(const T* rhs) const { return ptr != rhs; }

  bool operator!=(T* rhs) const { return ptr != rhs; }

  static cont_it begin(T* begin) noexcept { return cont_it(begin); }
  static cont_it end(T* end)     noexcept { return cont_it(end); }

  const T* base() const { return ptr; }

private:

  T* ptr {nullptr};
};

