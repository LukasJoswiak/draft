#include "../binary.hpp"

#ifndef STRING_HPP_
#define STRING_HPP_

namespace draft {

void Save(BinaryOutputArchive&oa, const std::string& str) {
  oa(str.size());
  oa.SaveToBinary(std::addressof(str), sizeof(str));
}

}  // namespace draft

#endif  // STRING_HPP_
