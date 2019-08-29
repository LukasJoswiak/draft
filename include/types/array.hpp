// Serialization logic for std::array. Can be improved by reusing the logic
// for raw array serialization (see binary_output.hpp). Access the underlying
// array with .data().

#ifndef INCLUDE_ARRAY_HPP_
#define INCLUDE_ARRAY_HPP_

#include <algorithm>
#include <array>

#include "../binary_output.hpp"
#include "../binary_input.hpp"

namespace draft {
namespace binary {

// Serialize the array by encoding each element individually.
template<typename T, std::size_t N>
void Save(OutputArchive&oa, std::array<T, N>& array) {
  std::for_each(array.begin(), array.end(), oa);
}

// Load the array from the given binary input archive by reading elements
// and storing them one at a time in `array`.
template<typename T, std::size_t N>
void Load(binary::InputArchive& ia, std::array<T, N>& array) {
  std::for_each(array.begin(), array.end(), ia);
}

}  // namespace binary
}  // namespace draft

#endif  // INCLUDE_ARRAY_HPP_
