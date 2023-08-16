#include <array.hpp>
#include <ut.hpp>

namespace ut = boost::ut;

// template<typename T, size_t S>
// using array = edgs::array<T, S>;

/**
 * @brief tests for simple small int array
 *
 */
// ut::suite<"edgs::array"> test_array = [] 

template < template <typename T, size_t N> typename array, ut::fixed_string Name>
ut::suite<Name> test_array = [] 
{
  using namespace boost::ut;
  using namespace boost::ut::spec;

  constexpr size_t SIZE = 5;

  describe("constructors") = [] {
    it("should default construct to zeros") = [] {
      array<int, 5> a{};
      auto n = a.data();
      expect(n[0] == 0 && n[1] == 0 &&
             n[2] == 0 && n[3] == 0 && n[4] == 0);
    };

    it("should construct from initalizer list") = [] {
      array<int, 5> a{1, 2, 3, 4, 5};
      auto n = a.data();
      expect(n[0] == 1 && n[1] == 2 &&
             n[2] == 3 && n[3] == 4 && n[4] == 5 );
    };

    it("should construct from initalizer list leaving zeros") = [] {
      array<int, 5> a{1, 2};
      auto n = a.data();
      expect(n[0] == 1 && n[1] == 2 &&
             n[2] == 0 && n[3] == 0 && n[4] == 0 );
    };

    it("should construct from raw array") = [] {
      int raw[5]{1, 2 , 3, 4, 5};
      auto a = array<int, 5>(raw);
      auto n = a.data();
      expect(n[0] == 1 && n[1] == 2 &&
             n[2] == 3 && n[3] == 4 && n[4] == 5 );
    };

    it("should construct from raw array leaving zeros") = [] {
      int raw[5]{1, 2};
      auto a = array<int, 5>(raw);
      auto n = a.data();
      expect(n[0] == 1 && n[1] == 2 &&
             n[2] == 0 && n[3] == 0 && n[4] == 0 );
    };
  };

  describe("copies") = [] {
    it("should copy its conents") = [] {
      array<int, 5> a{2, 2, 2, 2};
      array<int, 5> b = a;
      // expect(a[0] == b[0] && a[1] == b[1]);
      a[0] = 9;
      expect(a[0] == 9 && b[0] == 2);
    };
  };


  describe("capacity functions") = [] {
    array<int, 5> a = {1, 2, 3, 4, 5};
    it("shold return array size") = [&]{
      expect(a.size() == SIZE);
    };

    it("shold return that array is not empty") = [&]{
      expect(a.empty() == false);
    };
  };

  describe("acces with operator[]") = [] {

    it("should return init values ") = [&] {
      array<int, 5> a = {1, 2, 3, 4, 5};
      expect(a[0] == 1 && a[1] == 2 &&
             a[2] == 3 && a[3] == 4 && a[4] == 5 );
    };

    it("should insert element") = [&] {
      array<int, 5> a = {};
      expect(a[0] == 0);
      a[0] = 1; a[1] = 2;
      expect(a[0] == 1 && a[1] == 2);
    };

    it("should should be able to use [] with const array") = [&] {
      const array<int, 5> a = {1, 2, 3};
      expect(a[0] == 1 && a[1] == 2 &&
             a[2] == 3 );
    };
  };

  describe("iterators" )   = [] {
    using array_it = typename array<int, 5>::array_it;
    array<int, 5> a = {1, 0, 0, 0, 2};

    it("should point to start of array data") = [&] {
      array_it it = a.begin();
      const int& it_ref = it.operator*();
      expect(it_ref == *a.data());
      expect(it.base() == a.data());
    };

    it("should point to next element of array data and back to first") = [&] {
      array_it it = a.begin();
      ++it;
      expect(it.base() == a.data() + 1);
      --it;
      expect(it.base() == a.data() && *it == a[0]);
    };

    it("begin() should point to first element") = [&] {
      expect(a.begin().base() == a.data() &&
             a.begin().base() == &a[0]);
    };

    it("end() should point to last element") = [&] {
      expect(a.end().base() == a.data() + SIZE &&
             a.end().base() == &a[SIZE]);
    };

    it("should be able to iterate in range based for loop") = [] {
      array<int, 5> a = {1, 0, 0, 0, 2};
      int count = 0;

      for (int it : a) {
        if(count == 0) expect(it == 1);
        if(count == 4) expect(it == 2);
        count++;
      }
    };
  };

  describe("acces with at()") = [] {

    it("should throw an exception when invalid index") = [&] {
      array<int, 5> a = {1, 2, 3, 4, 5};
      // expect(throws([&] {
      //     a.at(-1);
      // }));

      expect(throws([&] {
          a.at(999);
      }));

      expect(nothrow([&] {
          a.at(0);
      }));
    };

    it("should be able to call from const array") = [] {
      const array<int, 5> a = {1, 2, 3, 4, 5};
      expect(a.at(0) == 1);
    };

  };
};

inline auto s1 = test_array<edgs::array, "edgs::array">;
// TODO
// static auto s2 = test_array< std::array, "std::array">;

