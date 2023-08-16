#include <ut.hpp>
#include <map>
#include <map.hpp>

#include <allocator.hpp>

namespace ut = boost::ut;

// template<typename K, typename V>
// using map = edgs::map<K, V>;
// using map = std::map<K, V,
//       std::less<K>,
//       edgs::allocator<std::pair<const K, V> 
//       >>;

/**
 * @brief tests for simple map
 *
 */
template < template <typename... T> typename map, ut::fixed_string Name>
ut::suite<Name> test_map = [] 
{
  using namespace boost::ut;
  using namespace boost::ut::spec;

  describe("constructors") = [] {
    it("should construt empty map") = [] {
      map<int, char> m;
      expect(m.size() == 0 && m.empty());
    };

    it("should construt from initalizer list") = [] {
      map<int, char> m = {
        {1, 'a'},
        {2, 'b'},
        {3, 'c'},
      };
      auto it = m.begin();
      expect(m.size() == 3 && !m.empty());
      expect(  (it)->first == 1 && it->second == 'a' &&
             (++it)->first == 2 && it->second == 'b' &&
             (++it)->first == 3 && it->second == 'c');
    };
  };

  describe("modifiers") = [] {

    it("should insert values on empty map") = [] {
      map<int, char> m;
      m.insert({1, 'a'});
      m.insert({2, 'b'});
      auto r = m.insert({3, 'c'});
      expect(m.size() == 3 && !m.empty() &&
             r.second == true);
    };

    it("should not be able to insert duplicates") = [] {
      map<int, char> m;
      m.insert({1, 'a'});
      auto r = m.insert({1, 'a'});
      expect(m.size() == 1 && !m.empty() &&
             r.second == false);
    };

    it("should clear map") = [] {
      map<int, char> m;
      m.clear();
      expect(m.size() == 0 && m.empty());
    };
  };

  describe("access") = [] {

    it("should update value or add value") = [] {
      map<int, char> m = { {1, 'a'}, {2, 'b'}, {3, 'c'}};
      m[1] = '1';
      m[5] = '5';
      expect(m[1] == '1' && m[2] == 'b' && m[5] == '5');
    };

    it("should insert default value if non existing key") = [] {
      map<int, char> m = { {1, 'a'}, {2, 'b'}, {3, 'c'}};
      auto t = m[5];
      expect(t == '\0' && m[5] == '\0');
    };

    it("should insert default value if non existing key float") = [] {
      map<int, float> m = { {1, 0.1f}, {2, 0.2f}, {3, 0.3f}};
      auto t = m[5];
      expect(t == 0.f && m[5] == 0.f);
    };

    it("should return value of key") = [] {
      map<int, char> m = { {1, 'a'}, {2, 'b'}, {3, 'c'}};
      expect(m.at(1) == 'a' && m.at(2) == 'b');
    };

    it("should throw exception if invalid at()") = [] {
      map<int, char> m = { {1, 'a'}, {2, 'b'}, {3, 'c'}};
      expect(
        throws([&] { m.at(0);   }) &&
        throws([&] { m.at(999); }) 
      );
      expect(nothrow([&] { m.at(1); }));
    };
  };

  describe("iterators" )   = [] {

    it("should point to past-the-end empty") = [] {
      map<int, char> m;
      auto it = m.begin();
      expect(it == m.end());
    };

    it("should point to past-the-end" ) = [] {
      map<int, char> m { {1, 'c'} };
      auto it = m.begin();
      ++it;
      expect(it == m.end());
    };

    it("begin == end if not empty") = [] {
      map<int, char> m { {1, 'c'}, {2, 'b'} };
      expect(m.begin() != m.end() && m.size() == 2);
    };

  };

  describe("looup") = [] {

    it("shoud return if contains a key") = [] {
      map<int, char> m = { {1, 'a'}, {2, 'b'}, {3, 'c'}};
      expect(m.contains(1) && m.contains(2));
    };

    it("shoud be able to return value given [key]") = [] {
      map<int, char> m = { {1, 'a'}, {2, 'b'}, {3, 'c'}};
      expect(m[1] == 'a' && m[2] == 'b' && m[3] == 'c');
    };

    it("should count no duplicates") = [] {
      map<int, char> m;
      m.insert({1, 'a' });
      m.insert({1, 'a' });
      expect(m.count(1) == 1);
    };

    it("upper_bound should return next possible element in map") = [] {
      map<int, char> m{ {8, '8'}, {2, '2'}, {5, '5'}, {4, '4'} };
      auto it = m.upper_bound(0);
      expect(it->first == 2 && it->second == '2');
      it = m.upper_bound(2);
      expect(it->first == 4 && it->second == '4');
      it = m.upper_bound(3);
      expect(it->first == 4 && it->second == '4');
    };

    it("lower_bound should return next possible element in map") = [] {
      map<int, char> m{ {8, '8'}, {2, '2'}, {5, '5'}, {4, '4'} };
      auto it = m.lower_bound(0);
      expect(it->first == 2 && it->second == '2');
      it = m.lower_bound(2);
      expect(it->first == 2 && it->second == '2');
      it = m.lower_bound(3);
      expect(it->first == 4 && it->second == '4');
    };
  };

};

inline auto s1 = test_map<edgs::map, "edgs::map">;
inline auto s2 = test_map< std::map, "std::map">;
