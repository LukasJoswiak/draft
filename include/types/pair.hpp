// std::pair is encoded by encoding its first element followed by encoding
// its second element. Type information must be provided to determine how
// many bytes to write when serializing and how many bytes to read when
// deserializing.
//
// Both types of the pair must be serializable to serialize the pair.

#ifndef INCLUDE_PAIR_HPP_
#define INCLUDE_PAIR_HPP_

#include "../binary_output.hpp"
#include "../binary_input.hpp"

namespace draft {
namespace binary {

// Save the pair by writing its elements. Both elements must be
// serializable.
template<typename T1, typename T2>
void Save(OutputArchive&oa, std::pair<T1, T2>& pair) {
  oa(pair.first);
  oa(pair.second);
}

// Load the pair from the given binary input archive into pair. Type info
// must be provided to determine how many bytes of the input archive to
// read.
template<typename T1, typename T2>
void Load(binary::InputArchive& ia, std::pair<T1, T2>& pair) {
  ia(pair.first);
  ia(pair.second);
}

}  // namespace binary
}  // namespace draft

#endif  // INCLUDE_PAIR_HPP_
