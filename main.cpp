#include <fstream>
#include <iostream>

#include <include/draft.hpp>

int main() {
  {
    std::ofstream stream("out", std::ios::binary);
    draft::BinaryOutputArchive oa(stream);

    std::string str("hello");
    oa(32, str);

    // Try running `xxd -b out` on the command line to view the binary
    // dump of `out`.
  }

  {
    std::ifstream stream("out", std::ios::binary);
    draft::BinaryInputArchive ia(stream);

    int x;
    std::string str;
    ia(x, str);
    std::cout << x << ", " << str << std::endl;
  }

  return 0;
}
