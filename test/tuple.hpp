#include <sstream>

#include <catch2/catch.hpp>
#include <include/draft.hpp>

TEST_CASE("std::tuple can be serialized") {
  std::stringstream ss;
  draft::binary::OutputArchive oa(ss);
  draft::binary::InputArchive ia(ss);

  SECTION("encode tuple with one basic lvalue") {
    int x = 99;
    std::tuple<int> t = std::make_tuple(x);
    oa(t);
    std::tuple<int> u;
    ia(u);

    REQUIRE(std::get<0>(u) == x);
  }

  SECTION("encode tuple with one basic rvalue") {
    std::tuple<int> t = std::make_tuple(7);
    oa(t);
    std::tuple<int> u;
    ia(u);

    REQUIRE(std::get<0>(u) == 7);
  }

  SECTION("encode tuple with multiple basic rvalues") {
    std::tuple<char, double, bool> t = std::make_tuple('a', 3.14, true);
    oa(t);
    std::tuple<char, double, bool> u;
    ia(u);

    REQUIRE(std::get<0>(u) == 'a');
    REQUIRE(std::get<1>(u) == 3.14);
    REQUIRE(std::get<2>(u) == true);
  }

  SECTION("encode tuple with multiple rvalues") {
    std::tuple<int, std::string, std::pair<float, int>> t =
        std::make_tuple(5, "hello", std::make_pair(0.99, 1));
    oa(t);
    std::tuple<int, std::string, std::pair<float, int>> u;
    ia(u);

    REQUIRE(std::get<0>(u) == 5);
    REQUIRE(std::get<1>(u) == "hello");
    // std::pair overloads operator==, so this comparison will work as expected
    REQUIRE(std::get<2>(u) == std::make_pair((float) 0.99, 1));
  }

  SECTION("encode nested tuple") {
    std::tuple<int, std::tuple<int>> t = std::make_tuple(1, std::make_tuple(2));
    oa(t);
    std::tuple<int, std::tuple<int>> u;
    ia(u);

    REQUIRE(std::get<0>(u) == 1);
    // std::pair overloads operator==, so this comparison will work as expected
    REQUIRE(std::get<1>(u) == std::make_tuple(2));
  }
}
