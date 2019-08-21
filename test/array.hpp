#include <sstream>

#include <catch2/catch.hpp>
#include <include/draft.hpp>

TEST_CASE("raw arrays can be serialized") {
  std::stringstream ss;
  draft::binary::OutputArchive oa(ss);
  draft::binary::InputArchive ia(ss);

  SECTION("encode array of fundamental types") {
    int a[3] = {1, 2, 3};
    oa(arr);
    int b[3];
    ia(b);

    REQUIRE(b[0] == 1);
    REQUIRE(b[1] == 2);
    REQUIRE(b[2] == 3);
  }

  SECTION("encode array of objects") {
    std::string a[2] = {"hello", "world"};
    oa(arr);
    std::string b[2];
    ia(b);

    REQUIRE(b[0] == "hello");
    REQUIRE(b[1] == "world");
  }
}

TEST_CASE("std::array can be serialized") {
  SECTION("encode array of fundamental types") {
    std::array<int, 3> a{1, 2, 3};
    oa(arr);
    std::array<int, 3> b;
    ia(b);

    REQUIRE(b[0] == 1);
    REQUIRE(b[1] == 2);
    REQUIRE(b[2] == 3);
  }

  SECTION("encode array of objects") {
    std::array<std::string, 2> a{"hello", "world"};
    oa(arr);
    std::array<std::string, 2> b;
    ia(b);

    REQUIRE(b[0] == "hello");
    REQUIRE(b[1] == "world");
  }
}
