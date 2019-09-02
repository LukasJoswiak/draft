// Serialization logic for std::queue. The default underlying container used
// by the queue is std::deque, but this can be specified by the user.

#ifndef INCLUDE_QUEUE_HPP_
#define INCLUDE_QUEUE_HPP_

#include <queue>

#include "../binary_output.hpp"
#include "../binary_input.hpp"

namespace draft {
namespace binary {

// Serialize the queue by encoding its underlying container. Container must be
// a serializable type. Access to the underlying container is protected, so the
// following is done to get around the protected member object issue.
template<typename T, typename Container>
void Save(OutputArchive& oa, const std::queue<T, Container>& queue) {
  // TODO: implement (serialize queue.c)
}

// TODO: comment
template<typename T, typename Container>
void Load(binary::InputArchive& ia, std::queue<T, Container>& queue) {
  // TODO: implement
}

}  // namespace binary
}  // namespace draft

#endif  // INCLUDE_QUEUE_HPP_
