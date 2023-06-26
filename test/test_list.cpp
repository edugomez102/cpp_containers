#include <list>
#include <list.hpp>
#include <ut.hpp>

namespace ut = boost::ut;

template<typename T>
using list = edgs::list<T>;

/**
 * @brief tests for simple small int list
 *
 */
ut::suite<"edgs::list"> test_list = [] 
{
  using namespace boost::ut;
  using namespace boost::ut::spec;

  describe("constructor") = [] {
    it("should create an empty list") = []{
      list<int> a;
      expect(a.size() == 0 && a.empty());
    };

    it("should create list from value") = []{
      list<int> a(5, 9);
      expect(a.size() == 5 && a.front() == 9 &&
             a.back() == 9);
    };

    it("should assign values") = []{
      list<int> a;
      a.assign(5, 9);
      expect(a.size() == 5 && a.front() == 9 &&
             a.back() == 9);
    };

    it("should create from initializer list") = []{
      list<int> a = {1, 2, 3, 4};
      expect(a.size() == 4 && a.front() == 1 &&
             a.back() == 4);
    };

  };

  describe("modifiers") = [] {
    it("should push_back values") = []{
      list<int> a;
      a.push_back(1);
      a.push_back(2);
      expect(a.front() == 1 && a.back() == 2 && a.size() == 2);
    };
    it("should push_front values") = []{
      list<int> a;
      a.push_front(1);
      a.push_front(2);
      expect(a.front() == 2 && a.back() == 1 && a.size() == 2);
    };
    it("should push_front and push_back values") = []{
      list<int> a = { 2 };
      a.push_front(1);
      a.push_back(3);
      expect(a.front() == 1 && a.back() == 3 && a.size() == 3);
    };

    it("should clear the list") = []{
      list<int> a = {1, 2, 3};
      expect(a.front() == 1 && a.back() == 3 && a.size() == 3);
      a.clear();
      expect(a.size() == 0 && a.empty());
    };

    it("should delete last element") = [] {
      list<int> a = {1, 2, 3};
      a.pop_back();
      expect(a.back() == 2 && a.size() == 2);
    };

    it("should delete first element") = [] {
      list<int> a = {1, 2, 3};
      a.pop_front();
      expect(a.front() == 2 && a.size() == 2);
    };

    it("should erase element in the middle") = [] {
      list<int> a{1, 2, 3};
      auto it = a.begin();
      ++it; // 2
      auto erased_next = a.erase(it); // next element from ersase
      expect(a.size() == 2 && *erased_next == 3);
    };

    it("should erase first element") = [] {
      list<int> a{1, 2, 3};
      auto it = a.begin();
      auto erased_next = a.erase(it); // next element from ersase
      expect(a.size() == 2 && *erased_next == 2 && a.front() == 2);
    };
  };

  describe("iterators" )   = [] {

    using list_it = list<int>::iterator;

    it("should point to start of list") = [&] {
      list<int> a = {1, 0, 0, 0, 2};
      list_it it = a.begin();
      const int& it_data = it.operator*();
      expect(it_data == a.front());
    };

    // it("should point to last") = [] {
    //   list<int> a = {1, 2, 9};
    //   list_it it = a.end();
    //   expect(*it == --a.back());
    // };

    it("should be able to iterate in range based for loop") = [] {
      list<int> a = {1, 0, 0, 0, 2};
      a.push_back(9);
      a.pop_back();
      a.push_front(9);
      a.pop_front();
      int count = 0;

      for (int it : a) {
        if(count == 0) expect(it == 1);
        if(count == 4) expect(it == 2);
        count++;
      }
    };

    it("begin == end if empty") = [&] {
      list<int> a;
      expect(a.begin() == a.end() && a.size() == 0);
    };
  };

};
