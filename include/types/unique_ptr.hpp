// std::unique_ptr is encoded by encoding the object it manages. When
// deserializing, the object is read in and given to the unique pointer to
// manage.

#ifndef INCLUDE_UNIQUE_PTR_HPP_
#define INCLUDE_UNIQUE_PTR_HPP_

#include "../binary_output.hpp"
#include "../binary_input.hpp"

namespace draft {
namespace binary {

// Save the unique pointer by writing the managed element to the output stream.
template<typename T>
void Save(OutputArchive&oa, std::unique_ptr<T>& ptr) {
  oa(*ptr);
}

// Read the serialized element and give it to the smart pointer to manage.
template<typename T>
void Load(binary::InputArchive& ia, std::unique_ptr<T>& ptr) {
  T t;
  ia(t);
  ptr.reset(new T(t));
}

}  // namespace binary
}  // namespace draft

#endif  // INCLUDE_UNIQUE_PTR_HPP_
