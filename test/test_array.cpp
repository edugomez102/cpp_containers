#include <array.hpp>
#include <ut.hpp>
#include <array>

namespace ut = boost::ut;

template<typename T, size_t S>
using array = edgs::array<T, S>;

/**
 * @brief tests for simple small int array
 *
 */
ut::suite<"edgs::array"> sprite_test = [] 
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
      array<int, 5> a = {1, 2, 3, 4, 5};
      auto n = a.data();
      expect(n[0] == 1 && n[1] == 2 &&
             n[2] == 3 && n[3] == 4 && n[4] == 5 );
    };

    it("should construct from initalizer list leaving zeros") = [] {
      array<int, 5> a = {1, 2};
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

  describe("functions") = [] {
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
    array<int, 5> a = {1, 0, 0, 0, 2};

    it("begin() should point to first element") = [&] {
      expect(a.begin() == a.data() &&
            *a.begin() == a[0]);
    };

    it("end() should point to last element") = [&] {
      expect(a.end() == a.data() + SIZE &&
            *a.end() == a[SIZE]);
    };
  };

  describe("acces with at()") = [] {

    it("should throw an exception when invalid index") = [&] {
      array<int, 5> a = {1, 2, 3, 4, 5};
      expect(throws([&] {
          a.at(-1);
      }));

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

