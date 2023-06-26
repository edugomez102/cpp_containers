#include <ut.hpp>
#include <utility>
#include <pair.hpp>

namespace ut = boost::ut;

ut::suite<"edgs::pair"> pair_test = []
{
  using namespace boost::ut;
  using namespace boost::ut::spec;

  using namespace edgs;

  it("should default") = [] {
    pair<int, float> p;
    expect(p.first == 0 && p.second == 0);
  };

  it("should construct") = [] {
    pair<int, float> p{1, 1.0f};
    expect(p.first == 1 && p.second == 1.0f);
  };

  it("should copy construct") = [] {
    pair<int, float> p1{1, 1.0f};
    pair<int, float> p2(p1);
    expect(p2.first == 1 && p2.second == 1.0f);
  };

  it("should move construct") = [] {
    pair<int, float> p1{1, 1.0f};
    pair<int, float> p2(move(p1));
    expect(p2.first == 1 && p2.second == 1.0f);
  };

  it("should compare") = [] {
    pair<int, float> p1{1, 1.0f};
    pair<int, float> p2{1, 1.0f};
    expect(p1 == p2);
  };

  it("should copy") = [] {
    pair<int, float> p1{1, 1.0f};
    pair<int, float> p2 = p1;
    expect(p1 == p2);
  };

  it("should move") = [] {
    pair<int, float> p1{1, 1.0f};
    pair<int, float> p2 = {1, 1.0f};
    auto p4 = p1;
    pair<int, float> p3 = move(p4);
    expect(p1 == p2 && p1 == p3);
  };

  it("should swap") = [] {
    pair<int, float> p1{1, 1.0f};
    pair<int, float> p2{2, 2.0f};
    p1.swap(p2);
    expect(p1.first == 2 && p1.second == 2.0f &&
           p2.first == 1 && p2.second == 1.0f);
  };

  it("should make_pair") = [] {
    auto p = make_pair(4, 'a');
    expect(p.first == 4 && p.second == 'a');
  };
};
