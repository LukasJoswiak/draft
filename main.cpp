#include <fstream>
#include <iostream>

#include <include/draft.hpp>

int main() {
  {
    std::ofstream stream("out", std::ios::binary);
    draft::BinaryOutputArchive oa(stream);

    oa(32);
    // oa("hello");
    // oa(std::string("hi"));

    // Try running `xxd -b out` on the command line to view the binary
    // dump of `out`.
  }

  {
    std::ifstream stream("out", std::ios::binary);
    draft::BinaryInputArchive ia(stream);

    int a;
    ia(a);
    std::cout << "a = " << a << std::endl;
  }

  return 0;
}
