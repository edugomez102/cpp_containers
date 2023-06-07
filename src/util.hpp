#include <cstddef>

namespace edgs {

  template <typename T>
  void copy(T* start, T* end, T* target)
  {
    T* p_start  = start;
    T* p_target = target;

    for (size_t i = 0; i < size_t(end - start); i++) {
      *p_target = *p_start;
      ++p_start;
      ++p_target;
    }
  };
}

