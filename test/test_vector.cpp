
#include <vector.hpp>
#include <ut.hpp>

namespace ut = boost::ut;

template<typename T>
using vector = edgs::vector<T>;

/**
 * @brief tests for simple small int array
 *
 */
ut::suite<"edgs::vector"> vector_test = [] 
{
  using namespace boost::ut;
  using namespace boost::ut::spec;


  describe("constructors and capacity") = [] {
    it("should contruct empty vector of size 1") = [] {
      vector<int> v;
      expect(v.capacity() == 1 && v.size() == 0 
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
    };
  };

  describe("modifiers") = [] {
    it("should add new elements") = [] {
      vector<int> v{1, 2, 3, 4};
      v.push_back(5);
    };

  };


};
