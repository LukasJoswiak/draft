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

  SECTION("encode boolean") {
    bool x = true;
    oa(x);
    bool y;
    ia(y);

    REQUIRE(y == true);
  }

  SECTION("encode char") {
    char x = 'd';
    oa(x);
    char y;
    ia(y);

    REQUIRE(y == 'd');
  }

  SECTION("encode floating point value") {
    float x = 3.14;
    oa(x);
    float y;
    ia(y);

    // Equality of floating point should work because the encoding
    // of the original float and the deserialized float are
    // exactly the same.
    REQUIRE(y == 3.14f);
  }

  SECTION("encode double floating point value") {
    double x = 1.0 / 31;
    oa(x);
    double y;
    ia(y);

    REQUIRE(y == 1.0 / 31);
  }
}
