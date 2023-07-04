#include <set.hpp>
#include <ut.hpp>
#include <set>

namespace ut = boost::ut;

template<typename T>
using set = edgs::set<T>;

/**
 * @brief tests for simple set
 *
 */
ut::suite<"edgs::set"> set_test = [] 
{
  using namespace boost::ut;
  using namespace boost::ut::spec;

  describe("constructors and capacity") = [] {
    it("should construct empty") = [] {
      edgs::set<int> s;
      expect(s.size() == 0 && s.empty());
    };

    it("should construct from initializer list ") = [] {
      edgs::set<int> s{4, 9, 2};
      auto it = s.begin();
      expect(
              *it == 2 &&
          *(++it) == 4 &&
          *(++it) == 9 && s.size() == 3);
    };

  };

  describe("modifiers") = [] {

    it("should insert") = [] {
      edgs::set<int> s;
      s.insert(1);
      s.insert(2);
      expect(*s.begin()  == 1 && *(++s.begin()) == 2);
    };

    it("should not insert duplicate") = [] {
      edgs::set<int> s;
      s.insert(1);
      auto result = s.insert(1);
      expect(result.second == false && s.size() == 1);
    };

    it("should insert and reorder") = [] {
      edgs::set<int> s;
      s.insert(8);
      s.insert(2);
      s.insert(5);
      s.insert(4);
      s.insert(9); // 2 4 5 8 9
      auto it = s.begin();
      expect(
              *it == 2 &&
          *(++it) == 4 &&
          *(++it) == 5 &&
          *(++it) == 8 &&
          *(++it) == 9 );
    };

    it("should clear") = [] {
      edgs::set<int> s{4, 9, 2};
      expect(s.size() == 3 && !s.empty());
      s.clear();
      expect(s.size() == 0 && s.empty());
    };
  };

  describe("iterators" )   = [] {

    it("should point to past-the-end empty") = [] {
      set<int> s;
      auto it = s.begin();
      ++it;
      expect(it == s.end());
    };

    it("should point to past-the-end") = [] {
      set<int> s{1};
      auto it = s.begin();
      ++it;
      ++it;
      expect(it == s.end());
    };

    it("begin == end if empty") = [] {
      set<int> s;
      expect(s.begin() == s.end() && s.size() == 0);
    };

    it("begin == end if not empty") = [] {
      set<int> s{1, 2, 3};
      expect(s.begin() != s.end() && s.size() == 3);
    };
  };

  describe("lookup" )  = [] {

    it("should contain and find") = [] {
      edgs::set<int> s;
      s.insert(1);
      expect(s.contains(1) && *s.find(1) == 1 );
    };

    it("should count") = [] {
      edgs::set<int> s;
      s.insert(8);
      s.insert(8);
      expect(s.count(8) == 1);
    };
  };



  // "empty set"_test = [] {
  //   set<int> s;
  //   s.begin();
  //   expect(s.empty());
  //   expect(s.size() == 0);
  // };
  //
  // "insertion and size"_test = [] {
  //   set<int> s;
  //   s.insert(42);
  //   s.insert(10);
  //   s.insert(99);
  //   expect(s.size() == 3);
  // };

  // "containment check"_test = [] {
  //   set<int> s{1, 2, 3};
  //   expect(s.contains(2));
  //   expect(!s.contains(4));
  // };
  //
  // "deletion"_test = [] {
  //   set<int> s{1, 2, 3};
  //   s.erase(2);
  //   expect(!s.contains(2));
  //   expect(s.size() == 2);
  // };
  //
  // "clear"_test = [] {
  //   set<int> s{1, 2, 3};
  //   s.clear();
  //   expect(s.empty());
  //   expect(s.size() == 0);
  // };
  //
  // "count"_test = [] {
  //   set<int> s{1, 2, 3};
  //   expect(s.count(2) == 1);
  //   expect(s.count(4) == 0);
  // };
  //
  // "range-based for loop"_test = [] {
  //   set<int> s{1, 2, 3};
  //   int sum = 0;
  //   for (const auto& element : s) {
  //     sum += element;
  //   }
  //   expect(sum == 6);
  // };
  //
  // "lower_bound"_test = [] {
  //   set<int> s{1, 3, 5};
  //   auto it = s.lower_bound(4);
  //   expect(*it == 5);
  // };
  //
  // "upper_bound"_test = [] {
  //   set<int> s{1, 3, 5};
  //   auto it = s.upper_bound(2);
  //   expect(*it == 3);
  // };
  //
  // "equal_range"_test = [] {
  //   set<int> s{1, 3, 5};
  //   auto [lower, upper] = s.equal_range(3);
  //   expect(*lower == 3);
  //   expect(*upper == 5);
  // };
  //
  // "copy constructor"_test = [] {
  //   set<int> s{1, 2, 3};
  //   set<int> copy(s);
  //   expect(copy == s);
  // };
  //
  // "move constructor"_test = [] {
  //   set<int> s{1, 2, 3};
  //   set<int> moved(std::move(s));
  //   expect(moved.size() == 3);
  //   expect(s.empty());
  // };
  //
  // "copy assignment operator"_test = [] {
  //   set<int> s{1, 2, 3};
  //   set<int> copy;
  //   copy = s;
  //   expect(copy == s);
  // };
  //
  // "move assignment operator"_test = [] {
  //   set<int> s{1, 2, 3};
  //   set<int> moved;
  //   moved = std::move(s);
  //   expect(moved.size() == 3);
  //   expect(s.empty());
  // };
  //
  // "swap"_test = [] {
  //   set<int> s1{1, 2, 3};
  //   set<int> s2{4, 5, 6};
  //   s1.swap(s2);
  //   expect(s1.size() == 3);
  //   expect(s2.size() == 3);
  // };
  //
  // "insert duplicate"_test = [] {
  //   set<int> s{1, 2, 3};
  //   auto [it, success] = s.insert(2);
  //   expect(*it == 2);
  //   expect(!success);
  //   expect(s.size() == 3);
  // };
  //
  // "insert range"_test = [] {
  //   set<int> s{1, 2, 3};
  //   std::vector<int> values{4, 5, 6};
  //   s.insert(values.begin(), values.end());
  //   expect(s.size() == 6);
  // };
  //
  // "erase range"_test = [] {
  //   set<int> s{1, 2, 3, 4, 5};
  //   s.erase(s.begin(), s.find(4));
  //   expect(s.size() == 2);
  //   expect(s.contains(4));
  //   expect(s.contains(5));
  // };
  //
  // "erase by value"_test = [] {
  //   set<int> s{1, 2, 3};
  //   s.erase(2);
  //   expect(!s.contains(2));
  //   expect(s.size() == 2);
  // };
  //
  // "comparison operators"_test = [] {
  //   set<int> s1{1, 2, 3};
  //   set<int> s2{2, 3, 4};
  //   set<int> s3{1, 2, 3};
  //
  //   expect(s1 != s2);
  //   expect(s1 == s3);
  //   expect(s1 < s2);
  //   expect(s2 > s1);
  //   expect(s1 <= s3);
  //   expect(s2 >= s1);
  // };

};
