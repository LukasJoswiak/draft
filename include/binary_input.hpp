#ifndef INCLUDE_BINARY_INPUT_HPP_
#define INCLUDE_BINARY_INPUT_HPP_

#include <cassert>
#include <fstream>
#include <memory>

namespace draft {
namespace binary {

class InputArchive {
 public:
  explicit InputArchive(std::istream& istrm) : istrm_(istrm) {
    // Make sure serialized data was written correctly by checking
    // the magic number written to the first four bytes.
    uint32_t magic_number;
    LoadBinary(std::addressof(magic_number), sizeof(magic_number));
    assert(magic_number == 0xabbaface && "Could not read serialized file");
  }

  // Overload the function call operator. This allows clients to
  // pass an arbitrary number of parameters to be populated with
  // data based on the archived data.
  // Unlike the output class, the input class does not accept rvalues.
  // It does not make sense to accept rvalues because there is no
  // mechanism to give the deserialized data back to the caller if the
  // passed in object is an rvalue.
  template<typename... Types>
  void operator()(Types&... args) {
    Process(args...);
  }

  // Read `size` characters from the archive and store them in the
  // location `addr` points to.
  void LoadBinary(void* addr, std::size_t size) const {
    istrm_.read(reinterpret_cast<char*>(addr), size);
  }

 private:
  template<typename T>
  void Process(T& first) {
    Load(*this, first);
  }

  template<typename T, typename... Types>
  void Process(T& first, Types&... rest) {
    Process(first);
    Process(rest...);
  }

  std::istream& istrm_;
};

// Deserialze arithmetic types.
template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value>::type
Load(const InputArchive& ia, T& t) {
  ia.LoadBinary((void*) std::addressof(t), sizeof(t));
}

// Deserialize class types.
template<typename T>
typename std::enable_if<std::is_class<T>::value>::type
Load(InputArchive& ia, T& t) {
  t.Serialize(ia);
}

// To deserialize arrays, deserialize each element individually.
template<typename T>
typename std::enable_if<std::is_array<T>::value>::type
Load(InputArchive& ia, T& t) {
  for (const auto& val : t) {
    ia(val);
  }
}

}  // namespace binary
}  // namespace draft

#endif  // INCLUDE_BINARY_INPUT_HPP_
