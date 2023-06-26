#include <vector.hpp>
#include <ut.hpp>
#include <vector>

namespace ut = boost::ut;

template<typename T>
// using vector = std::vector<T>;
using vector = edgs::vector<T>;

/**
 * @brief tests for simple small int vector
 *
 */
ut::suite<"edgs::vector"> vector_test = [] 
{
  using namespace boost::ut;
  using namespace boost::ut::spec;

  describe("constructors and capacity") = [] {
    it("should construct empty vector of size 0") = [] {
      vector<int> v;
      expect(v.capacity() == 0 && v.size() == 0 
          && v.empty());
    };

    it("should contruct vector of size 4, filled with 1") = [] {
      auto v = vector<int>(4, 1);
      expect(v.capacity() == 4 && v.size() == 4) << "size";
      expect(v.data()[0] == 1 && v.data()[1] == 1 &&
             v.data()[2] == 1 && v.data()[3] == 1) << "values";
    };

    it("should contruct vector from initalizer list") = [] {
      vector<int> v{1, 2, 3, 4};
      expect(v[0] == 1 && v[1] == 2 &&
             v[2] == 3 && v[3] == 4);
      expect(v.capacity() == 4 && v.size() == 4);
    };
  };

  describe("modifiers") = [] {
    it("should add new element to vector empty") = [] {
      vector<int> v;
      v.push_back(1);
      expect(v[0] == 1) << "element";
      expect(v.size() == 1 && v.capacity() == 1) << "size";
    };

    it("should add new element to vector") = [] {
      vector<int> v{1, 2, 3, 4};
      v.push_back(5);
      expect(v[v.size() - 1] == 5) << "element";
    };

    it("should add new element to empty vector") = [] {
      vector<int> v;
      v.push_back(1);
      v.push_back(2);
      v.push_back(3);
      expect(v.at(0) == 1 && v.at(1) == 2 &&
             v.at(2) == 3 ) << "elements";
      expect(v.size() == 3) << "size";
    };

    it("should be able to change element with operator[]") = [] {
      vector<int> v{1, 2};
      v[0] = 9; v[1] = 9;
      expect(v[0] == 9 && v[1] == 9);
    };

    it("should remove last element and decrease size") = [] {
      vector<int> v{1, 2};
      v.pop_back();
      expect(v[0] == 1 && v.size() == 1 && v.capacity() == 2);
    };

    it("should clear the vector int") = [] {
      vector<int> v{1, 2, 3, 4};
      v.clear();
      expect(v.capacity() == 4 && v.size() == 0);
    };

    it("should insert element at begin") = [] {
      edgs::vector<int> v{1, 2, 3};

      auto r = v.insert(v.begin(), 9);
      expect(v[0] == 9 && *r.base() == 9 );
    };

    it("should insert element at the end") = [] {
      edgs::vector<int> v{1, 2, 3};

      auto r = v.insert(v.end(), 9);
      expect(v[3] == 9 && *r.base() == 9 );
    };

    it("should insert element at middle and increase capacity") = [] {
      edgs::vector<int> v{1, 2, 3, 0};

      const auto precapacity = v.capacity();
      auto r = v.insert(v.begin() + 2, 9);
      expect(v[2] == 9 && *r.base() == 9  &&
          precapacity < v.capacity());
    };
    it("should insert const element at begin") = [] {
      edgs::vector<int> v{1, 2, 3};

      const int value = 5;
      auto r = v.insert(v.begin(), value);
      expect(v[0] == 5 && *r.base() == 5 );
    };

    // "should insert element at given position"_test = [] {
    //   vector<std::string> v{"one", "three"};
    //   auto it = v.insert(v.begin() + 1, "two");
    //   expect(v.size() == 3 && v[0] == "one" && v[1] == "two" && v[2] == "three" );
    // };
  };

  describe("iterators" )   = [] {

    using vector_it = vector<int>::iterator;
    vector<int> a = {1, 0, 0, 0, 2};

    it("should point to start of array data") = [&] {
      vector_it it = a.begin();
      const int& it_ref = it.operator*();
      expect(it_ref == *a.data());
      expect(it.base() == a.data());
    };

    it("should point to next element of array data and back to first") = [&] {
      vector_it it = a.begin();
      ++it;
      expect(it.base() == a.data() + 1);
      --it;
      expect(it.base() == a.data() && *it == a[0]);
    };

    it("begin() should point to first element") = [&] {
      expect(a.begin().base() == a.data() &&
             a.begin() .base()== &a[0]);
    };

    it("end() should point to last element") = [&] {
      expect(a.end().base() == a.data() + a.size() &&
             a.end().base() == &a[a.size()]);
    };

    it("should point to last") = [] {
      std::vector<int> v{1, 2, 3};
      expect(*(v.end() - 1) == 3);
    };

    describe("const version") = [] {
      const vector<int> a = {1, 0, 0, 0, 2};

      it("begin() should point to first element") = [&] {
        expect(a.begin().base() == a.data() &&
               a.begin() .base()== &a[0]);
      };

      it("end() should point to last element") = [&] {
        expect(a.end().base() == a.data() + a.size() &&
               a.end().base() == &a[a.size()]);
      };;
    };

    it("should be able to iterate in range based for loop") = [] {
      vector<int> a = {1, 0, 0, 0, 2};
      int count = 0;

      for (int it : a) {
        if(count == 0) expect(it == 1);
        if(count == 4) expect(it == 2);
        count++;
      }
    };
  };

};
