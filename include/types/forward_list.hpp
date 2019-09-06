// Serialization logic for std::forward_list.

#ifndef INCLUDE_FORWARD_LIST_HPP_
#define INCLUDE_FORWARD_LIST_HPP_

#include <algorithm>
#include <forward_list>

#include "../binary_output.hpp"
#include "../binary_input.hpp"

namespace draft {
namespace binary {

// Serialize the forward list by encoding its size, then encoding  each element
// individually.
template<typename T, typename Allocator>
void Save(OutputArchive&oa, std::forward_list<T, Allocator>& list) {
  // std::forward_list has no size() member, so manually determine the size.
  auto size = std::distance(list.begin(), list.end());
  oa(size);

  std::for_each(list.begin(), list.end(), oa);
}

// Deserialize the forward_list by reading the number of elements stored, then
// reading each element.
template<typename T, typename Allocator>
void Load(binary::InputArchive& ia, std::forward_list<T, Allocator>& list) {
  typename std::forward_list<T, Allocator>::size_type size;
  ia(size);

  // Resize the forward_list to make room for the correct number of elements.
  list.resize(size);

  std::for_each(list.begin(), list.end(), ia);
}

}  // namespace binary
}  // namespace draft

#endif  // INCLUDE_FORWARD_LIST_HPP_
