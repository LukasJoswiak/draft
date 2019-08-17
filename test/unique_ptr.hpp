#include <sstream>

#include <catch2/catch.hpp>
#include <include/draft.hpp>

TEST_CASE("std::unique_ptr with a single object can be serialized") {
  std::stringstream ss;
  draft::binary::OutputArchive oa(ss);
  draft::binary::InputArchive ia(ss);

  SECTION("encode unique_ptr to int") {
    int val = 99;
    std::unique_ptr<int> p(new int(val));
    oa(p);
    std::unique_ptr<int> q;
    ia(q);

    REQUIRE(*q == val);
  }

  SECTION("encode unique_ptr to string") {
    std::unique_ptr<std::string> p(new std::string("pointer"));
    oa(p);
    std::unique_ptr<std::string> q;
    ia(q);

    REQUIRE(*q == "pointer");
  }
}

TEST_CASE("std::unique_ptr with an array of objects can be serialized") {
  std::stringstream ss;
  draft::binary::OutputArchive oa(ss);
  draft::binary::InputArchive ia(ss);

  SECTION("encode unique_ptr to array of ints") {
    std::unique_ptr<int[]> p(new int[2]);
    p[0] = 1;
    p[1] = 6;
    oa(p);
    std::unique_ptr<int[]> q;
    ia(q);

    REQUIRE(q[0] == 1);
    REQUIRE(q[1] == 6);
  }
}
