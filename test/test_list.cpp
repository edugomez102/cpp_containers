#include <list>
#include <list.hpp>
#include <ut.hpp>
#include <util.hpp>

#include <allocator.hpp>

namespace ut = boost::ut;

/**
 * @brief tests for simple small int list
 *
 */
template < template <typename... T> typename list, ut::fixed_string Name>
ut::suite<Name> test_list = [] 
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

    it("should copy list") = []{
      list<int> a = {1, 2, 3, 4};
      list<int> b = a;
      expect(a.size() == 4 && a.front() == 1 &&
             a.back() == 4);
      expect(b.size() == 4 && b.front() == 1 &&
             b.back() == 4);
      auto it = b.begin();
      expect(   *it == 1 &&
            *(++it) == 2 &&
            *(++it) == 3 &&
            *(++it) == 4 );
    };

    // it("move") = [] {
    //   list<int> originalList;
    //   for (int i = 1; i <= 5; ++i) {
    //     originalList.push_back(i);
    //   }
    //
    //   list<int> movedList = std::move(originalList);
    //   expect(originalList.empty());
    //
    //   int expectedValue = 1;
    //   for (const auto& value : movedList) {
    //     expect(value == expectedValue);
    //     ++expectedValue;
    //   }
    // };

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

    using list_it = typename list<int>::iterator;

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

inline auto s1  = test_list<edgs::list, "edgs::list">;
inline auto s2  = test_list< std::list, "std::list">;

