// Serialization logic for std::unordered_map.

#ifndef INCLUDE_UNORDERED_MAP_HPP_
#define INCLUDE_UNORDERED_MAP_HPP_

#include <unordered_map>

#include "../binary_output.hpp"
#include "../binary_input.hpp"

namespace draft {
namespace binary {

// Serialize the unordered_map by writing the number of elements it holds,
// then writing each key-value pair in order.
template<typename K, typename V>
void Save(OutputArchive& oa, const std::unordered_map<K, V>& map) {
  // TODO: implement
}

// Deserialize the unordered_map by reading the number of elements stored,
// then reading each key-value pair.
template<typename K, typename V>
void Load(binary::InputArchive& ia, std::unordered_map<K, V>& map) {
  // TODO: implement
}

}  // namespace binary
}  // namespace draft

#endif  // INCLUDE_UNORDERED_MAP_HPP_
