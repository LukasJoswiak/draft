#include <fstream>
#include <iostream>

namespace draft {

class BinaryOutputArchive {
 public:
  BinaryOutputArchive(std::ostream &ostrm);

  // Overload the function call operator. This allows clients to use instances
  // of this class as a function.
  template <typename T, typename... ArgTypes>
  void operator()(T t, ArgTypes... args) {
    process(t, args...);
  }

 private:
  template <typename T>
  void process(T first) {
    std::cout << first << std::endl;
  }

  template <typename T, typename... ArgTypes>
  void process(T first, ArgTypes... rest) {
    std::cout << first << std::endl;

    process(rest...);
  }
};

}  // namespace draft
