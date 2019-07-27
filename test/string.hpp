#include <sstream>

#include <catch2/catch.hpp>
#include <include/draft.hpp>

TEST_CASE("strings can be serialized") {
  std::stringstream ss;
  draft::binary::OutputArchive oa(ss);
  draft::binary::InputArchive ia(ss);

  // Short strings use SSO to avoid using the heap for storage.
  // Make sure this optimization does not affect serialization.
  SECTION("encode short string") {
    std::string str("a");
    oa(str);
    std::string res;
    ia(res);

    REQUIRE(res == "a");
  }

  SECTION("encode long string") {
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::string str(alphabet);
    oa(str);
    std::string res;
    ia(res);

    REQUIRE(res == alphabet);
  }

  // TODO: Add tests for other string types in the future (when
  // std::basic_string is supported)
}
