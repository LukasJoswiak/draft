// Serialization logic for std::list.

#ifndef INCLUDE_LIST_HPP_
#define INCLUDE_LIST_HPP_

#include <list>

#include "../binary_output.hpp"
#include "../binary_input.hpp"

namespace draft {
namespace binary {

// Serialize the list by encoding its size, then encoding  each element
// individually.
template<typename T, typename Allocator>
void Save(OutputArchive&oa, std::list<T, Allocator>& list) {
  oa(list.size());
  std::for_each(list.begin(), list.end(), oa);
}

// Deserialize the list by reading the number of elements stored, then reading
// each element.
template<typename T, typename Allocator>
void Load(binary::InputArchive& ia, std::list<T, Allocator>& list) {
  typename std::list<T, Allocator>::size_type size;
  ia(size);

  // Resize the list to make room for the correct number of elements.
  list.resize(size);

  std::for_each(list.begin(), list.end(), ia);
}

}  // namespace binary
}  // namespace draft

#endif  // INCLUDE_LIST_HPP_
