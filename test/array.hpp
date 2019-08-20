#include <sstream>

#include <catch2/catch.hpp>
#include <include/draft.hpp>

TEST_CASE("raw arrays can be serialized") {
  std::stringstream ss;
  draft::binary::OutputArchive oa(ss);
  draft::binary::InputArchive ia(ss);

  SECTION("encode array with fundamental types") {
    int a[3] = {1, 2, 3};
    oa(arr);
    int b[5];
    ia(b);

    REQUIRE(b[0] == 1);
    REQUIRE(b[1] == 2);
    REQUIRE(b[2] == 3);
  }
}

TEST_CASE("std::array can be serialized") {

}
