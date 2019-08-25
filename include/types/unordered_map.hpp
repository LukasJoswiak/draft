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
  oa(map.size());
  for (const auto& kv : map) {
    oa(kv.first);
    oa(kv.second);
  }
}

// Deserialize the unordered_map by reading the number of elements stored,
// then reading each key-value pair.
template<typename K, typename V>
void Load(binary::InputArchive& ia, std::unordered_map<K, V>& map) {
  // Read in size of map.
  std::size_t size;
  ia(size);

  for (int i = 0; i < size; ++i) {
    K key;
    V value;
    ia(key);
    ia(value);

    // Let the map take control of `key` and `value` to avoid having to make
    // copies.
    // TODO: This can likely be improved by using emplace_hint instead.
    map.emplace(std::move(key), std::move(value));
  }
}

}  // namespace binary
}  // namespace draft

#endif  // INCLUDE_UNORDERED_MAP_HPP_
