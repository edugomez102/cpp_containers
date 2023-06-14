#include <ut.hpp>
#include <util.hpp>
#include <memory>

namespace ut = boost::ut;

/**
 * @brief tests for utility functions
 *
 */
ut::suite<"edgs::util"> util_test = [] 
{
  using namespace boost::ut;
  using namespace boost::ut::spec;

  it("should copy from origin array to targe array") = [] {

    constexpr size_t SIZE = 4;
    int o[SIZE] = {1, 2, 3, 4};
    int t[SIZE] = {};
    edgs::copy(o, o + SIZE, t);

    expect(t[0] == 1 && t[1] == 2 && 
           t[2] == 3 && t[3] == 4);
  };

  it("shoud be able to move basic type") = [] {
    std::unique_ptr<int> p{};
    auto up = std::make_unique<int>(50);
    p = edgs::move(up);
    expect(up == nullptr && *p.get() == 50);
  };

};
