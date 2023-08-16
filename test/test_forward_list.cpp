
#include <forward_list>
#include <forward_list.hpp>
#include <ut.hpp>

namespace ut = boost::ut;

// template<typename T>
// using forward_list = edgs::forward_list<T>;

/**
 * @brief tests for simple small int forward_list
 *
 */
// ut::suite<"edgs::forward_list"> test_forward_list = [] 
template < template <typename... T> typename forward_list, ut::fixed_string Name>
ut::suite<Name> test_forward_list = [] 
{
  using namespace boost::ut;
  using namespace boost::ut::spec;

  describe("constructor") = [] {
  };

  it("should construct") = [] {
    forward_list<int> l;
    l.push_front(1);
    l.push_front(2);
    l.push_front(3);
    auto it = l.begin();
    expect(   *it == 3 &&
          *(++it) == 2 &&
          *(++it) == 1 );
  };
  it("shoud construct assign") = [] {
    forward_list<int> l(4, 7);
    auto it = l.begin();
    expect(   *it == 7 &&
          *(++it) == 7 &&
          *(++it) == 7 &&
          *(++it) == 7 );
  };
  it("should create from initializer list") = []{
    forward_list<int> l{1, 2, 3, 4, 5};
    auto it = l.begin();
    expect(   *it == 1 &&
          *(++it) == 2 &&
          *(++it) == 3 &&
          *(++it) == 4 &&
          *(++it) == 5 );
  };

  it("shoud assign") = [] {
    forward_list<int> l;
    l.assign(4, 7);
    auto it = l.begin();
    expect(   *it == 7 &&
          *(++it) == 7 &&
          *(++it) == 7 &&
          *(++it) == 7 );
  };

  describe("modifiers") = [] {
    it("should push_front values") = []{
      forward_list<int> a;
      a.push_front(1);
      a.push_front(2);
      expect(a.front() == 2);
    };

    it("should clear the forward_list") = []{
      forward_list<int> a = {1, 2, 3};
      expect(a.front() == 1);
      a.clear();
      expect(a.empty());
    };


    it("should delete first element") = [] {
      forward_list<int> a = {1, 2, 3};
      a.pop_front();
      expect(a.front() == 2 );
    };
  };

  it("should point to start of forward_list") = [&] {
    forward_list<int> a = {1, 0, 0, 0, 2};
    auto it = a.begin();
    expect(*it == a.front());
  };

  it("begin == end if empty") = [&] {
    forward_list<int> a;
    expect(a.begin() == a.end());
  };

};

// inline auto s1 = test_forward_list<edgs::forward_list, "edgs::forward_list">;
// inline auto s2 = test_forward_list< std::forward_list, "std::forward_list">;

