#ifndef INCLUDE_BINARY_INPUT_HPP_
#define INCLUDE_BINARY_INPUT_HPP_

#include <fstream>
#include <memory>

namespace draft {
namespace binary {

class InputArchive {
 public:
  explicit InputArchive(std::istream& istrm) : istrm_(istrm) {}

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

// Deserialze arithmetic types.
template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value>::type
Load(const InputArchive& ia, T& t) {
  ia.LoadBinary(std::addressof(t), sizeof(t));
}

// Deserialize class types.
template<typename T>
typename std::enable_if<std::is_class<T>::value>::type
Load(const InputArchive& ia, T& t) {
  ia.LoadBinary(std::addressof(t), sizeof(t));
}

}  // namespace binary
}  // namespace draft

#endif  // INCLUDE_BINARY_INPUT_HPP_
