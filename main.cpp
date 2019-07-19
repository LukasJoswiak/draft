#include <fstream>
#include <iostream>

#include <include/draft.hpp>

int main() {
  {
    std::ofstream stream("out", std::ios::binary);
    draft::BinaryOutputArchive oa(stream);

    // oa(32);
    oa("hello");

    // Try running `xxd -b out` on the command line to view the binary
    // dump of `out`.
  }

  return 0;
}
