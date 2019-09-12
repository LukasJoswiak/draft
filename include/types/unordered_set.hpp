// Serialization logic for std::unordered_set.

#ifndef INCLUDE_UNORDERED_SET_HPP_
#define INCLUDE_UNORDERED_SET_HPP_

#include <unordered_set>

#include "../binary_output.hpp"
#include "../binary_input.hpp"

namespace draft {
namespace binary {

// Serialize the unordered set by encoding its size, then encoding  each element
// individually.
template<typename Key, typename Hash, typename KeyEqual, typename Allocator>
void
Save(OutputArchive&oa,
    std::unordered_set<Key, Hash, KeyEqual, Allocator>& set) {
  oa(set.size());
  std::for_each(set.begin(), set.end(), oa);
}

// TODO: Combine serialization for std::unordered_set and
// std::unordered_multiset into a single function.
// Add support for std::unordered_multiset as well.
template<typename Key, typename Hash, typename KeyEqual, typename Allocator>
void
Save(OutputArchive&oa,
    std::unordered_multiset<Key, Hash, KeyEqual, Allocator>& set) {
  oa(set.size());
  std::for_each(set.begin(), set.end(), oa);
}

// Deserialize the unordered set by reading the number of elements stored, then
// reading each element.
template<typename Key, typename Hash, typename KeyEqual, typename Allocator>
void
Load(binary::InputArchive& ia,
    std::unordered_set<Key, Hash, KeyEqual, Allocator>& set) {
  typename std::unordered_set<Key, Hash, KeyEqual, Allocator>::size_type size;
  ia(size);

  for (std::size_t i = 0; i < size; ++i) {
    Key key;
    ia(key);

    // TODO: This can likely be improved by using emplace_hint instead.
    set.emplace(std::move(key));
  }
}

// Support std::unordered_multiset deserialization.
template<typename Key, typename Hash, typename KeyEqual, typename Allocator>
void
Load(binary::InputArchive& ia,
    std::unordered_multiset<Key, Hash, KeyEqual, Allocator>& set) {
  typename
      std::unordered_multiset<Key, Hash, KeyEqual, Allocator>::size_type size;
  ia(size);

  for (std::size_t i = 0; i < size; ++i) {
    Key key;
    ia(key);

    set.emplace(std::move(key));
  }
}

}  // namespace binary
}  // namespace draft

#endif  // INCLUDE_UNORDERED_SET_HPP_
