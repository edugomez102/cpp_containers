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

  it("shoud be able to move int array") = [] {
    const size_t S = 3;
    int a[S] = {1, 2, 3};
    int b[S];
    edgs::move(a, a + S, b);
    expect(b[0] == 1 and b[1] == 2 and b[2] == 3);
  };

  it("shoud be able to move uniqueptr int array") = [] {
    std::array<std::unique_ptr<int>, 4> a{
      std::make_unique<int>(1),
      std::make_unique<int>(2),
      std::make_unique<int>(3),
      std::make_unique<int>(4),
    };
    std::array<std::unique_ptr<int>, 4> b;
    edgs::move(a.begin(), a.end(), b.begin());

    expect(*b[0] == 1 and *b[1] == 2 and *b[2] == 3);
    expect(a[0].get() == nullptr and
           a[1].get() == nullptr and
           a[2].get() == nullptr);

  };

};
