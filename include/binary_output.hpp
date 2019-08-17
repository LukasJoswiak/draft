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
  // t can be either an lvalue reference or an rvalue reference, depending
  // on what is passed in to the functor. This is important because it allows
  // serialization of both lvalues and rvalues.
  //
  // To maintain the reference type of t when passing it to the next function,
  // std::forward is used. Inside this function, t is an lvalue reference,
  // and passing it to the next function without std::forward means the next
  // function would only be able to accept an lvalue.
  template<typename T, typename... Types>
  void operator()(T&& t, Types&&... args) {
    Process(std::forward<T>(t), args...);
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
  void Process(T&& first, Types&&... rest) {
    Process(std::forward<T>(first));
    Process(std::forward<Types>(rest)...);
  }

  std::ostream& ostrm_;
};

// The compiler will generate a function with the appropriate type if T
// passes the `is_arithmetic` check, i.e. T is an int or float.
template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value>::type
Save(OutputArchive& oa, const T& t) {
  oa.SaveToBinary(std::addressof(t), sizeof(t));
}

// Overload `Save` for class types (which should implement a `Serialize`
// function which determines the class members to use for serialization).
template<typename T>
typename std::enable_if<std::is_class<T>::value>::type
Save(OutputArchive& oa, const T& t) {
  t.Serialize(oa);
}

// Disable support for serialization of pointers. Pointers cannot be reliably
// deserialized because not all sections of memory are writable.
template<typename T>
typename std::enable_if<std::is_pointer<T>::value>::type
Save(OutputArchive& oa, const T& t) {
  // Check at compile time that T is not a pointer. This check will always
  // fail, because this function only gets called when T is a pointer.
  static_assert(!std::is_pointer<T>::value,
      "draft does not support serialization of raw pointers");
}

}  // namespace binary
}  // namespace draft

#endif  // INCLUDE_BINARY_OUTPUT_HPP_
