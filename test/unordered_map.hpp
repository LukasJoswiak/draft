#include <sstream>

#include <catch2/catch.hpp>
#include <include/draft.hpp>

TEST_CASE("std::unordered_map can be serialized") {
  std::stringstream ss;
  draft::binary::OutputArchive oa(ss);
  draft::binary::InputArchive ia(ss);

  SECTION("encode std::unordered_map of fundamental types") {
    std::unordered_map<int, double> m = {
      { 1, 3.14 },
      { 100, 9.99 }
    };
    oa(m);
    std::unordered_map<int, double> n;
    ia(n);

    REQUIRE(n.size() == 2);
    REQUIRE(n.count(1) == 1);
    REQUIRE(n.count(100) == 1);
    REQUIRE(n.at(1) == 3.14);
    REQUIRE(n.at(100) == 9.99);
  }

  SECTION("encode std::unordered_map of objects") {
    std::unordered_map<int, std::string> m = {
      { 1, "hello" },
      { 2, "world" }
    };
    oa(m);
    std::unordered_map<int, std::string> n;
    ia(n);

    REQUIRE(n.size() == 2);
    REQUIRE(n.count(1) == 1);
    REQUIRE(n.count(2) == 1);
    REQUIRE(n.at(1) == "hello");
    REQUIRE(n.at(2) == "world");
  }
}

TEST_CASE("std::unordered_multimap can be serialized") {
  std::stringstream ss;
  draft::binary::OutputArchive oa(ss);
  draft::binary::InputArchive ia(ss);

  SECTION("encode map of fundamental types") {
    std::unordered_multimap<int, double> m = {
      { 1, 3.14 },
      { 100, 9.99 },
      { 1, 600.5 }
    };
    oa(m);
    std::unordered_multimap<int, double> n;
    ia(n);

    REQUIRE(n.size() == 3);
    REQUIRE(n.count(1) == 2);
    REQUIRE(n.count(100) == 1);
  }

  SECTION("encode std::unordered_multimap of objects") {
    std::unordered_multimap<int, std::string> m = {
      { 1, "hello" },
      { 2, "world" },
      { 2, "draft" }
    };
    oa(m);
    std::unordered_multimap<int, std::string> n;
    ia(n);

    REQUIRE(n.size() == 3);
    REQUIRE(n.count(1) == 1);
    REQUIRE(n.count(2) == 2);
  }
}
