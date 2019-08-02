#include <sstream>

#include <catch2/catch.hpp>
#include <include/draft.hpp>

TEST_CASE("std::pair can be serialized") {
  std::stringstream ss;
  draft::binary::OutputArchive oa(ss);
  draft::binary::InputArchive ia(ss);

  SECTION("encode pair with basic types") {
    std::pair<int, int> p = std::make_pair(1, 2);
    oa(p);
    std::pair<int, int> q;
    ia(q);

    REQUIRE(q.first == p.first);
    REQUIRE(q.second == p.second);
  }

  SECTION("encode pair with object types") {
    std::pair<std::string, std::string> p = std::make_pair("hello", "world");
    oa(p);
    std::pair<std::string, std::string> q;
    ia(q);

    REQUIRE(q.first == p.first);
    REQUIRE(q.second == p.second);
  }

  SECTION("encode pair of pairs") {
    // Real world example: pair(id, pair(name, age))
    std::pair<int, std::pair<std::string, short>> p =
        std::make_pair(1234567, std::make_pair("Bill Gates", 21));
    oa(p);
    std::pair<int, std::pair<std::string, short>> q;
    ia(q);

    REQUIRE(q.first == p.first);
    REQUIRE(q.second.first == p.second.first);
    REQUIRE(q.second.second == p.second.second);
  }
}
