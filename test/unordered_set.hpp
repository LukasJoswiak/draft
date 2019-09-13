#include <sstream>

#include <catch2/catch.hpp>
#include <include/draft.hpp>

TEST_CASE("std::unordered_set can be serialized") {
  std::stringstream ss;
  draft::binary::OutputArchive oa(ss);
  draft::binary::InputArchive ia(ss);

  SECTION("encode unordered_set of fundamental types") {
    std::unordered_set<int> s{1, 66, 145};
    oa(s);
    std::unordered_set<int> t;
    ia(t);

    REQUIRE(t.size() == 3);
    REQUIRE(t.count(1) == 1);
    REQUIRE(t.count(66) == 1);
    REQUIRE(t.count(145) == 1);
  }

  SECTION("encode unordered_set of objects") {
    std::string draft("draft is a serialization library");
    std::unordered_set<std::string> s{"hello", "world", draft};
    oa(s);
    std::unordered_set<std::string> t;
    ia(t);

    REQUIRE(t.size() == 3);
    REQUIRE(t.count("hello") == 1);
    REQUIRE(t.count("world") == 1);
    REQUIRE(t.count(draft) == 1);
  }
}

TEST_CASE("std::unordered_multiset can be serialized") {
  std::stringstream ss;
  draft::binary::OutputArchive oa(ss);
  draft::binary::InputArchive ia(ss);

  SECTION("encode unordered_multiset of fundamental types") {
    std::unordered_multiset<int> s{1, 1, 66, 145, 66};
    oa(s);
    std::unordered_multiset<int> t;
    ia(t);

    REQUIRE(t.size() == 5);
    REQUIRE(t.count(1) == 2);
    REQUIRE(t.count(66) == 2);
    REQUIRE(t.count(145) == 1);
  }

  SECTION("encode unordered_multiset of objects") {
    std::string draft("draft is a serialization library");
    std::unordered_multiset<std::string> s{draft, "hello", "world", draft, "hello"};
    oa(s);
    std::unordered_multiset<std::string> t;
    ia(t);

    REQUIRE(t.size() == 5);
    REQUIRE(t.count("hello") == 2);
    REQUIRE(t.count("world") == 1);
    REQUIRE(t.count(draft) == 2);
  }
}
