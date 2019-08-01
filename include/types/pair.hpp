// TODO: comment

#ifndef INCLUDE_PAIR_HPP_
#define INCLUDE_PAIR_HPP_

#include "../binary_output.hpp"
#include "../binary_input.hpp"

namespace draft {
namespace binary {

// TODO: comment
template<typename T1, typename T2>
void Save(OutputArchive&oa, std::pair<T1, T2>& pair) {
  // TODO: implement
}

// TODO: comment
template<typename T1, typename T2>
void Load(binary::InputArchive& ia, std::pair<T1, T2>& pair) {
  // TODO: implement
}

}  // namespace binary
}  // namespace draft

#endif  // INCLUDE_PAIR_HPP_
