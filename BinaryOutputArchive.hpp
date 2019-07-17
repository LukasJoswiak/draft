#include <fstream>
#include <memory>

#ifndef BINARYOUTPUTARCHIVE_HPP_
#define BINARYOUTPUTARCHIVE_HPP_

namespace draft {

class BinaryOutputArchive {
 public:
  explicit BinaryOutputArchive(std::ostream& ostrm);

  // Overload the function call operator. This allows clients to use instances
  // of this class as a function. For example:
  //   draft::BinaryOutputArchive oa(<some output stream>);
  //   oa("hello", 32);
  template <typename T, typename... ArgTypes>
  void operator()(T t, ArgTypes... args) {
    Process(t, args...);
  }

 private:
  // Process and serialize a single element.
  template <typename T>
  void Process(T first) {
    Save(std::addressof(first), sizeof(first));
  }

  // Use variadic template to accept an arbitrary number of arguments. This
  // allows the user to pass any number of elements to be serialized.
  template <typename T, typename... ArgTypes>
  void Process(T first, ArgTypes... rest) {
    Process(first);
    Process(rest...);
  }

  // Write the given data to the output stream.
  void Save(const void* data, std::size_t size);

  std::ostream& ostrm_;
};

}  // namespace draft

#endif  // BINARYOUTPUTARCHIVE_HPP_
