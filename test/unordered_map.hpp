#include <sstream>

#include <catch2/catch.hpp>
#include <include/draft.hpp>

TEST_CASE("std::unordered_map can be serialized") {
  std::stringstream ss;
  draft::binary::OutputArchive oa(ss);
  draft::binary::InputArchive ia(ss);

  SECTION("encode map of fundamental types") {
    std::unordered_map<int, double> m = {
      { 1, 3.14 },
      { 100, 9.99 }
    };
    oa(m);
    std::unordered_map<int, double> n;
    ia(n);

    REQUIRE(n.count(1) == 1);
    REQUIRE(n.count(100) == 1);
    REQUIRE(n.at(1) == 3.14);
    REQUIRE(n.at(100) == 9.99);
  }

  SECTION("encode map of objects") {
    std::unordered_map<int, std::string> m = {
      { 1, "hello" },
      { 2, "world" }
    };
    oa(m);
    std::unordered_map<int, std::string> n;
    ia(n);

    REQUIRE(n.count(1) == 1);
    REQUIRE(n.count(2) == 1);
    REQUIRE(n.at(1) == "hello");
    REQUIRE(n.at(2) == "world");
  }
}
