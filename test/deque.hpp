#include <sstream>

#include <catch2/catch.hpp>
#include <include/draft.hpp>

TEST_CASE("std::deque can be serialized") {
  std::stringstream ss;
  draft::binary::OutputArchive oa(ss);
  draft::binary::InputArchive ia(ss);

  SECTION("encode deque of fundamental types") {
    std::deque<int> d = {1, 7, 6, 4};
    oa(d);
    std::deque<int> e;
    ia(e);

    REQUIRE(e.size() == 4);
    REQUIRE(e.at(0) == 1);
    REQUIRE(e.at(1) == 7);
    REQUIRE(e.at(2) == 6);
    REQUIRE(e.at(3) == 4);
  }

  SECTION("encode deque of objects") {
    std::string draft("draft is a serialization library");
    std::deque<std::string> d = {"hello", "world", draft};
    oa(d);
    std::deque<std::string> e;
    ia(e);

    REQUIRE(e.size() == 3);
    REQUIRE(e.at(0) == "hello");
    REQUIRE(e.at(1) == "world");
    REQUIRE(e.at(2) == draft);
  }
}
