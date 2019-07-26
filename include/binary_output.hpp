#ifndef INCLUDE_BINARY_OUTPUT_HPP_
#define INCLUDE_BINARY_OUTPUT_HPP_

#include <fstream>
#include <memory>

namespace draft {
namespace binary {

// TODO: Move HasSerialize to separate class

// Class to determine if generic `T` has a Serialize member function
// with matching return type and parameters defined in `call_serialize`.
template<typename T>
class HasSerialize {
  // Returns true if type `U` has function matching return type and
  // parameters defined here.
  template<typename U>
  static bool call_serialize(void (U::*) () const);

  // Returns true if type `U` has member function `Serialize` matching
  // function definition defined above.
  template<typename U>
  static std::true_type has_serialize(decltype(call_serialize(&U::Serialize)));

  // Catch all function. For any type of parameter which is not matched
  // above, this function will be called, which will always return false.
  template<typename U>
  static std::false_type has_serialize(...);

 public:
  // Test whether generic type `T` has Serialize function and store
  // result in `value`.
  static constexpr bool value = decltype(has_serialize<T>(nullptr)){};
};

class OutputArchive {
 public:
  explicit OutputArchive(std::ostream& ostrm) : ostrm_(ostrm) {}

  // Overload the function call operator. This allows clients to use instances
  // of this class as a function. For example:
  //   draft::binary::OutputArchive oa(<some output stream>);
  //   oa("hello", 32);
  //
  // It's important to accept rvalue references to maximize flexibility.
  // This allows calls of the format:
  //   std::string str("hello");
  //   oa(str.size());
  template<typename T, typename... ArgTypes>
  void operator()(T&& t, ArgTypes&&... args) {
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
  template<typename T, typename... ArgTypes>
  void Process(T&& first, ArgTypes&... rest) {
    Process(first);
    Process(rest...);
  }

  std::ostream& ostrm_;
};

// The compiler will generate a function with the appropriate type if T
// passes the is_arithmetic check, i.e. T is an int or float.
template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value>::type
Save(const OutputArchive& oa, const T& t) {
  oa.SaveToBinary(std::addressof(t), sizeof(t));
}

// TODO: Compiler error is unhelpful when trying to pass an object
// with no `Serialize` function to the output archive. Improve error.

// Overload `Save` for types which implement a `Serialize` function
// as defined in `HasSerialize`.
template<typename T>
typename std::enable_if<HasSerialize<T>::value>::type
Save(const OutputArchive& oa, const T& t) {
  t.Serialize();
}

}  // namespace binary
}  // namespace draft

#endif  // INCLUDE_BINARY_OUTPUT_HPP_
