#include <iostream>
#include <sstream>

#include <catch2/catch.hpp>

#include <include/draft.hpp>

TEST_CASE("basic types can be serialized") {
  std::stringstream ss;
  draft::binary::OutputArchive oa(ss);
  draft::binary::InputArchive ia(ss);

  SECTION("encode single integer") {
    int x = 1;
    oa(x);
    int y;
    ia(y);

    REQUIRE(y == 1);
  }

  SECTION("encode INT_MAX") {
    int x = 2147483647;
    oa(x);
    int y;
    ia(y);

    REQUIRE(y == 2147483647);
  }

  SECTION("encode INT_MAX") {
    double x = 3.14;
    oa(x);
    double y;
    ia(y);

    // Equality of floating point should work because the encoding
    // of the original double and the deserialized double are
    // exactly the same.
    REQUIRE(y == 3.14);
  }
}
