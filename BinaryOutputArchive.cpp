#include "BinaryOutputArchive.hpp"

namespace draft {

BinaryOutputArchive::BinaryOutputArchive(std::ostream& ostrm) : ostrm_(ostrm) {}

void BinaryOutputArchive::SaveToBinary(const void* addr, std::size_t size) const {
  ostrm_.write(reinterpret_cast<const char*>(addr), size);
}

}  // namespace draft
