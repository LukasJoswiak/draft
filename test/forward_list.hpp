#include <sstream>

#include <catch2/catch.hpp>
#include <include/draft.hpp>

TEST_CASE("std::forward_list can be serialized") {
  std::stringstream ss;
  draft::binary::OutputArchive oa(ss);
  draft::binary::InputArchive ia(ss);

  SECTION("encode forward_list of fundamental types") {
    std::forward_list<int> f{66, 123, 9, 8674};
    oa(f);
    std::forward_list<int> g;
    ia(g);

    REQUIRE(g.front() == 66);
    g.pop_front();
    REQUIRE(g.front() == 123);
    g.pop_front();
    REQUIRE(g.front() == 9);
    g.pop_front();
    REQUIRE(g.front() == 8674);
  }

  SECTION("encode forward_list of objects") {
    std::string draft("draft is a serialization library");
    std::forward_list<std::string> f{"hello", "world", draft};;
    oa(f);
    std::forward_list<std::string> g;
    ia(g);

    REQUIRE(g.front() == "hello");
    g.pop_front();
    REQUIRE(g.front() == "world");
    g.pop_front();
    REQUIRE(g.front() == draft);
  }
}
