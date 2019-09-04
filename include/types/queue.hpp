// Serialization logic for std::queue. The default underlying container used
// by the queue is std::deque, but this can be specified by the user.

#ifndef INCLUDE_QUEUE_HPP_
#define INCLUDE_QUEUE_HPP_

#include <queue>

#include "../binary_output.hpp"
#include "../binary_input.hpp"

namespace draft {
namespace binary {

// Return a reference to the underlying container of the given std::queue.
// See https://stackoverflow.com/a/29291621/986991 for an explanation of this
// code.
// TODO: Add inline explanatory comments.
template<typename T, typename C>
const C& UnderlyingContainer(const std::queue<T, C>& queue) {
  struct QueueInternals : private std::queue<T, C> {
    static const C& Container(const std::queue<T, C>& queue) {
      return queue .* &QueueInternals::c;
    }
  };
  return QueueInternals::Container(queue);
}

// Serialize the queue by encoding its underlying container. Container must be
// a serializable type.
template<typename T, typename Container>
void Save(OutputArchive& oa, const std::queue<T, Container>& queue) {
  oa(UnderlyingContainer(queue));
}

// Deserialize the queue by decoding its data into the underlying container
// type, then creating a new queue from the container data.
template<typename T, typename Container>
void Load(binary::InputArchive& ia, std::queue<T, Container>& queue) {
  auto container = UnderlyingContainer(queue);
  ia(container);
  queue = std::queue<T, Container>(std::move(container));
}

}  // namespace binary
}  // namespace draft

#endif  // INCLUDE_QUEUE_HPP_
