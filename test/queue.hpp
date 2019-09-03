#include <sstream>

#include <catch2/catch.hpp>
#include <include/draft.hpp>

TEST_CASE("std::queue can be serialized") {
  std::stringstream ss;
  draft::binary::OutputArchive oa(ss);
  draft::binary::InputArchive ia(ss);

  SECTION("encode queue of fundamental types") {
    std::queue<int> q;
    q.push(1);
    q.push(7);
    q.push(6);
    q.push(4);
    oa(q);
    std::queue<int> r;
    ia(r);

    REQUIRE(r.size() == 4);
    REQUIRE(r.front() == 1);
    r.pop();
    REQUIRE(r.front() == 1);
    r.pop();
    REQUIRE(r.front() == 1);
    r.pop();
    REQUIRE(r.front() == 1);
  }

  SECTION("encode queue of objects") {
    std::string draft("draft is a serialization library");
    std::queue<std::string> q;
    q.push("hello");
    q.push("world");
    q.push(draft);
    oa(q);
    std::queue<std::string> r;
    ia(r);

    REQUIRE(r.size() == 3);
    REQUIRE(r.front() == "hello");
    r.pop();
    REQUIRE(r.front() == "world");
    r.pop();
    REQUIRE(r.front() == draft);
  }
}
