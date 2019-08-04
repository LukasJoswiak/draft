#ifndef INCLUDE_BINARY_OUTPUT_HPP_
#define INCLUDE_BINARY_OUTPUT_HPP_

#include <fstream>
#include <memory>

namespace draft {
namespace binary {

class OutputArchive {
 public:
  explicit OutputArchive(std::ostream& ostrm) : ostrm_(ostrm) {
    // Write a unique value to the first four bytes of the output. This
    // is used to ensure compatibility when reading data for deserialization.
    const int magic_number = 0xabbaface;
    SaveToBinary(&magic_number, sizeof(magic_number));
  }

  // Overload the function call operator. This allows clients to use instances
  // of this class as a function. For example:
  //   draft::binary::OutputArchive oa(<some output stream>);
  //   oa("hello", 32);
  //
  // It's important to accept rvalue references to maximize flexibility.
  // This allows calls of the format:
  //   std::string str("hello");
  //   oa(str.size());
  template<typename T, typename... Types>
  void operator()(T&& t, Types&&... args) {
    Process(t, args...);
  }

  // Write the given data to the output stream.
  void SaveToBinary(const void* addr, std::size_t size) const {
    ostrm_.write(reinterpret_cast<const char*>(addr), size);
  }

 private:
  // Process and serialize a single element.
  template<typename T>
  void Process(T&& first) {
    Save(*this, first);
  }

  // Use variadic templates to accept an arbitrary number of arguments. This
  // allows the user to pass any number of elements to be serialized.
  template<typename T, typename... Types>
  void Process(T&& first, Types&... rest) {
    Process(first);
    Process(rest...);
  }

  std::ostream& ostrm_;
};

// The compiler will generate a function with the appropriate type if T
// passes the `is_arithmetic` check, i.e. T is an int or float.
template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value>::type
Save(OutputArchive& oa, T& t) {
  oa.SaveToBinary(std::addressof(t), sizeof(t));
}

// Overload `Save` for class types (which should implement a `Serialize`
// function which determines the class members to use for serialization).
template<typename T>
typename std::enable_if<std::is_class<T>::value>::type
Save(OutputArchive& oa, T& t) {
  t.Serialize(oa);
}

}  // namespace binary
}  // namespace draft

#endif  // INCLUDE_BINARY_OUTPUT_HPP_
