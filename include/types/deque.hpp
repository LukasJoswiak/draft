// Serialization logic for std::deque.

#ifndef INCLUDE_DEQUE_HPP_
#define INCLUDE_DEQUE_HPP_

#include <deque>

#include "../binary_output.hpp"
#include "../binary_input.hpp"

namespace draft {
namespace binary {

// Serialize the deque by writing its size, then writing each element. T must
// be a serializable type.
template<typename T, typename Allocator>
void Save(OutputArchive& oa, const std::deque<T, Allocator>& deque) {
  oa(deque.size());
  for (const auto& val : deque) {
    oa(val);
  }
}

// Deserialize the deque by reading its size and resizing the given deque.
// Then, write each element to the deque in order.
template<typename T, typename Allocator>
void Load(binary::InputArchive& ia, std::deque<T, Allocator>& deque) {
  std::size_t size;
  ia(size);

  // Resize the deque to make room for the right number of elements.
  deque.resize(size);

  // Loop through the deque and use the InputArchive to deserialize each
  // element (with type T) into its appropriate space in the deque.
  for (auto& val : deque) {
    ia(val);
  }
}

}  // namespace binary
}  // namespace draft

#endif  // INCLUDE_DEQUE_HPP_
