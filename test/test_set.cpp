#include <set.hpp>
#include <ut.hpp>
#include <set>

namespace ut = boost::ut;

// template<typename K>
// using set = edgs::set<K>;

/**
 * @brief tests for simple set
 *
 */
template < template <typename... T> typename set, ut::fixed_string Name>
ut::suite<Name> test_set = [] 
{
  using namespace boost::ut;
  using namespace boost::ut::spec;

  describe("constructors") = [] {
    it("should construct empty") = [] {
      set<int> s;
      expect(s.size() == 0 && s.empty());
    };

    it("should construct from initializer list ") = [] {
      set<int> s{4, 9, 2};
      auto it = s.begin();
      expect(
              *it == 2 &&
          *(++it) == 4 &&
          *(++it) == 9 && s.size() == 3);
    };

  };

  describe("modifiers") = [] {

    it("should insert") = [] {
      set<int> s;
      s.insert(1);
      s.insert(2);
      expect(*s.begin()  == 1 && *(++s.begin()) == 2);
    };

    it("should not insert duplicate") = [] {
      set<int> s;
      s.insert(1);
      auto result = s.insert(1);
      expect(result.second == false && s.size() == 1);
    };

    it("should insert and reorder") = [] {
      set<int> s;
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

    it("should construt, insert and reorder") = [] {
      set<int> s { 2, 3, 8};
      s.insert(5);
      s.insert(4);
      s.insert(9); // 2 3 4 5 8 9
      auto it = s.begin();
      expect(
          *(it++) == 2 &&
          *(it++) == 3 &&
          *(it++) == 4 &&
          *(it++) == 5 &&
          *(it++) == 8 &&
          *(it++) == 9 );
    };

    it("should clear") = [] {
      set<int> s{4, 9, 2};
      expect(s.size() == 3 && !s.empty());
      s.clear();
      expect(s.size() == 0 && s.empty());
    };
  };

  describe("iterators" )   = [] {

    it("should point to past-the-end empty") = [] {
      set<int> s;
      auto it = s.begin();
      expect(it == s.end());
    };

    it("should point to past-the-end") = [] {
      set<int> s{1};
      auto it = s.begin();
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
      set<int> s;
      s.insert(1);
      expect(s.contains(1) && *s.find(1) == 1 );
    };

    it("should count no duplicates") = [] {
      set<int> s;
      s.insert(8);
      s.insert(8);
      expect(s.count(8) == 1);
    };

    it("upper_bound should return next possible element in set") = [] {
      set<int> s{ 8, 2, 5, 4};
      auto it = s.upper_bound(0);
      expect(*it == 2);
      it = s.upper_bound(2);
      expect(*it == 4);
      it = s.upper_bound(3);
      expect(*it == 4);

    };

    it("invalid upper_bound index should return end") = [] {
      set<int> s;
      auto it = s.upper_bound(500);
      expect(it == s.end());
      it = s.upper_bound(-500);
      expect(it == s.end());

      set<int> s2{ 1 };
      it = s2.upper_bound(-500);
      expect(*it == 1);
      it = s2.upper_bound(500);
      expect(it == s.end());
      it = s2.upper_bound(1);
      expect(it == s.end());
    };

    it("lower_bound should return next possible element in set") = [] {
      set<int> s{ 8, 2, 5, 4};
      auto it = s.lower_bound(0);
      expect(*it == 2);
      it = s.lower_bound(2);
      expect(*it == 2);
      it = s.lower_bound(3);
      expect(*it == 4);
    };

    it("invalid lower_bound index should return end") = [] {
      set<int> s;
      auto it = s.lower_bound(500);
      expect(it == s.end());
      it = s.lower_bound(-500);
      expect(it == s.end());

      set<int> s2{ 1 };
      it = s2.lower_bound(-500);
      expect(*it == 1);
      it = s2.lower_bound(500);
      expect(it == s2.end());
      it = s2.lower_bound(1);
      expect(it != s2.end() && *it == 1);
    };
  };

};

inline auto s1 = test_set<edgs::set, "edgs::set">;
// TODO
// inline auto s2 = test_set< std::set, "std::set">;

