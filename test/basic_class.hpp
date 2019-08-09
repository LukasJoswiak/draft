#include <sstream>

#include <catch2/catch.hpp>
#include <include/draft.hpp>

class Point {
 public:
  Point() {}
  Point(int x, int y) : x_(x), y_(y) {}

  template<typename Archive>
  void Serialize(Archive& ar) const {
    ar(x_, y_);
  }

  int x_;
  int y_;
};

TEST_CASE("basic class can be serialized") {
  std::stringstream ss;
  draft::binary::OutputArchive oa(ss);
  draft::binary::InputArchive ia(ss);

  SECTION("encode simple Point instance") {
    Point p1(1, 2);
    oa(p1);
    Point p2;
    ia(p2);

    REQUIRE(p2.x_ == 1);
    REQUIRE(p2.y_ == 2);
  }
}
