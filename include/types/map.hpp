// Serialization logic for std::map.

#ifndef INCLUDE_MAP_HPP_
#define INCLUDE_MAP_HPP_

#include <map>

#include "../binary_output.hpp"
#include "../binary_input.hpp"

namespace draft {
namespace binary {

// Serialize the map by writing the number of elements it holds, then writing
// each key-value pair in order.
template<typename K, typename V, typename Compare, typename Allocator>
void Save(OutputArchive& oa, const std::map<K, V, Compare, Allocator>& map) {
  oa(map.size());
  for (const auto& kv : map) {
    oa(kv.first);
    oa(kv.second);
  }
}

// Deserialize the map by reading the number of elements stored, then reading
// each key-value pair.
template<typename K, typename V, typename Compare, typename Allocator>
void Load(binary::InputArchive& ia, std::map<K, V, Compare, Allocator>& map) {
  // Read in size of map.
  std::size_t size;
  ia(size);

  for (std::size_t i = 0; i < size; ++i) {
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

#endif  // INCLUDE_MAP_HPP_
