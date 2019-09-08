#include <sstream>

#include <catch2/catch.hpp>
#include <include/draft.hpp>

TEST_CASE("std::list can be serialized") {
  std::stringstream ss;
  draft::binary::OutputArchive oa(ss);
  draft::binary::InputArchive ia(ss);

  SECTION("encode list of fundamental types") {
    std::list<int> l{66, 123, 9, 8674};
    oa(l);
    std::list<int> m;
    ia(m);

    REQUIRE(m.front() == 66);
    m.pop_front();
    REQUIRE(m.front() == 123);
    m.pop_front();
    REQUIRE(m.front() == 9);
    m.pop_front();
    REQUIRE(m.front() == 8674);
  }

  SECTION("encode list of objects") {
    std::string draft("draft is a serialization library");
    std::list<std::string> l{"hello", "world", draft};;
    oa(l);
    std::list<std::string> m;
    ia(m);

    REQUIRE(m.front() == "hello");
    m.pop_front();
    REQUIRE(m.front() == "world");
    m.pop_front();
    REQUIRE(m.front() == draft);
  }
}
