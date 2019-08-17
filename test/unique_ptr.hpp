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
