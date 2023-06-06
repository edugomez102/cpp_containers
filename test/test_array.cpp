#include <array.hpp>
#include <ut.hpp>
#include <array>

namespace ut = boost::ut;

ut::suite<"edgs::array"> sprite_test = [] 
{
  using namespace boost::ut;
  using namespace boost::ut::spec;

  it("should have 4 values set to 0 raw array") = [&] {
    int n[4]{0};
    expect(n[0] == 0 && n[1] == 0 &&
           n[2] == 0 && n[3] == 0);
  };

  describe("constructors") = [] {
    it("should default construct to zeros") = [] {
      edgs::array<int, 5> a{};
      auto n = a.data();
      expect(n[0] == 0 && n[1] == 0 &&
             n[2] == 0 && n[3] == 0 && n[4] == 0);
    };

    it("should construct from initalizer list") = [] {
      edgs::array<int, 5> a = {1, 2, 3, 4, 5};
      auto n = a.data();
      expect(n[0] == 1 && n[1] == 2 &&
             n[2] == 3 && n[3] == 4 && n[4] == 5 );
    };

    it("should construct from initalizer list leaving zeros") = [] {
      edgs::array<int, 5> a = {1, 2};
      auto n = a.data();
      expect(n[0] == 1 && n[1] == 2 &&
             n[2] == 0 && n[3] == 0 && n[4] == 0 );
    };

    it("should construct from raw array") = [] {
      int raw[5]{1, 2 , 3, 4, 5};
      auto a = edgs::array<int, 5>(raw);
      auto n = a.data();
      expect(n[0] == 1 && n[1] == 2 &&
             n[2] == 3 && n[3] == 4 && n[4] == 5 );
    };

    it("should construct from raw array leaving zeros") = [] {
      int raw[5]{1, 2};
      auto a = edgs::array<int, 5>(raw);
      auto n = a.data();
      expect(n[0] == 1 && n[1] == 2 &&
             n[2] == 0 && n[3] == 0 && n[4] == 0 );
    };
  };

  describe("operator []") = [] {

    it("should return init values ") = [&] {
      edgs::array<int, 5> a = {1, 2, 3, 4, 5};
      expect(a[0] == 1 && a[1] == 2 &&
             a[2] == 3 && a[3] == 4 && a[4] == 5 );
    };

    it("should insert element") = [&] {
      edgs::array<int, 5> a = {};
      expect(a[0] == 0);
      a[0] = 1; a[1] = 2;
      expect(a[0] == 1 && a[1] == 2);
    };

    it("should should be able to use [] with const array") = [&] {
      const edgs::array<int, 5> a = {1, 2, 3};
      expect(a[0] == 1 && a[1] == 2 &&
             a[2] == 3 );
    };
  };

  describe("iterators" )   = [] {
    edgs::array<int, 5> a = {1, 0, 0, 0, 2};

    it("begin() should point to first element") = [&] {
      expect(a.begin() == a.data() &&
            *a.begin() == a[0]);
    };

    it("end() should point to last element") = [&] {
      expect(a.end() == a.data() + 5 &&
            *a.end() == a[5]);
    };
  };


};

