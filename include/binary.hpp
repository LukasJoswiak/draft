#include <fstream>
#include <iostream>
#include <memory>

#ifndef BINARYOUTPUTARCHIVE_HPP_
#define BINARYOUTPUTARCHIVE_HPP_

namespace draft {

class BinaryOutputArchive {
 public:
  explicit BinaryOutputArchive(std::ostream& ostrm) : ostrm_(ostrm) {}

  // Overload the function call operator. This allows clients to use instances
  // of this class as a function. For example:
  //   draft::BinaryOutputArchive oa(<some output stream>);
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

  // Use variadic template to accept an arbitrary number of arguments. This
  // allows the user to pass any number of elements to be serialized.
  template<typename T, typename... ArgTypes>
  void Process(T&& first, ArgTypes&... rest) {
    Process(first);
    Process(rest...);
  }

  std::ostream& ostrm_;
};

class BinaryInputArchive {
 public:
  explicit BinaryInputArchive(std::istream& istrm) : istrm_(istrm) {}

  // Overload the function call operator. This allows clients to
  // pass an arbitrary number of parameters to be populated with
  // data based on the archived data.
  template<typename... ArgTypes>
  void operator()(ArgTypes&&... args) {
    Process(args...);
  }

  // Read `size` characters from the archive and store them in the
  // location `addr` points to.
  void LoadBinary(void* addr, std::size_t size) const {
    istrm_.read(reinterpret_cast<char*>(addr), size);
  }

 private:
  template<typename T>
  void Process(T&& first) {
    Load(*this, first);
  }

  template<typename T, typename... ArgTypes>
  void Process(T&& first, ArgTypes&&... rest) {
    Process(first);
    Process(rest...);
  }

  std::istream& istrm_;
};

// The compiler will generate a function with the appropriate type if T
// passes the is_arithmetic check, i.e. T is an int or float.
template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value>::type
Save(const BinaryOutputArchive& oa, const T& t) {
  oa.SaveToBinary(std::addressof(t), sizeof(t));
}

// Deserialze arithmetic types.
template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value>::type
Load(const BinaryInputArchive& ia, T& t) {
  ia.LoadBinary(std::addressof(t), sizeof(t));
}

}  // namespace draft

#endif  // BINARYOUTPUTARCHIVE_HPP_
