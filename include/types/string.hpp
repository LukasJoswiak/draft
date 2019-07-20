// Strings are encoded by writing their size, followed by string itself.
// When decoding a string, the size is read in order to resize the string
// object being read into.
//
// The size of the string is written using std::size_t bytes, which is
// guaranteed to be large enough to represent the size of any object.
// On most systems this will be 8 bytes.

#ifndef STRING_HPP_
#define STRING_HPP_

#include "../binary_output.hpp"
#include "../binary_input.hpp"

namespace draft {

void Save(BinaryOutputArchive& oa, const std::string& str) {
  oa(str.size());
  oa.SaveToBinary(str.data(), sizeof(str));
}

void Load(BinaryInputArchive& ia, std::string& str) {
  // Read in size of string.
  uint64_t size;
  ia(size);

  // Resize string contain the correct number of characters.
  str.resize(size);

  // Read in string.
  ia.LoadBinary(str.data(), size);
}

}  // namespace draft

#endif  // STRING_HPP_
