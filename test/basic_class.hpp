#include <sstream>

#include <catch2/catch.hpp>
#include <include/draft.hpp>

class Point {
 public:
  Point() {}
  Point(int x, int y) : x_(x), y_(y) {}

  template<typename Archive>
  void Serialize(Archive& ar) {
    ar(x_, y_);
  }

  int x_;
  int y_;
};

TEST_CASE("class with arithmetic types can be serialized") {
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

class Person {
 public:
  Person() {}
  Person(std::string name, int age) : name_(name), age_(age) {}

  template<typename Archive>
  void Serialize(Archive& ar) {
    ar(name_, age_);
  }

  std::string name_;
  int age_;
};

TEST_CASE("class with object types can be serialized") {
  std::stringstream ss;
  draft::binary::OutputArchive oa(ss);
  draft::binary::InputArchive ia(ss);

  SECTION("encode simple Person instance") {
    Person p1("Ada", 204);
    oa(p1);
    Person p2;
    ia(p2);

    REQUIRE(p2.name_ == "Ada");
    REQUIRE(p2.age_ == 204);
  }
}
