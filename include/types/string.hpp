// Strings are encoded by writing their size, followed by the string itself.
// When decoding a string, the size is read in first in order to resize the
// string object being read into.
//
// The size of the string is written using std::size_t bytes, which is
// guaranteed to be large enough to represent the size of any object.
// On most systems this will be 8 bytes.

#ifndef INCLUDE_STRING_HPP_
#define INCLUDE_STRING_HPP_

#include <string>

#include "../binary_output.hpp"
#include "../binary_input.hpp"

namespace draft {
namespace binary {

// Save the string `str` to the binary output archive by saving its size,
// then its data.
template<typename CharT, typename Traits, typename Allocator>
void
Save(OutputArchive& oa,
    const std::basic_string<CharT, Traits, Allocator>& str) {
  oa(str.size());
  oa.SaveToBinary(str.data(), str.size());
}

// Read a string from the given binary input archive into str.
template<typename CharT, typename Traits, typename Allocator>
void
Load(binary::InputArchive& ia,
    std::basic_string<CharT, Traits, Allocator>& str) {
  // Read in size of string.
  uint64_t size;
  ia(size);

  // Resize string contain the correct number of characters.
  str.resize(size);

  // Read in string.
  ia.LoadBinary((void*) str.data(), size);
}

}  // namespace binary
}  // namespace draft

#endif  // INCLUDE_STRING_HPP_
