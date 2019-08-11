// std::tuple is more complicated to encode than std::pair, because std::tuple
// can contain an arbitrary number of elements of arbitrary types. Fortunately,
// these types are all known to us at compile time, meaning we can ensure each
// type in the tuple is serializable. The code in the anonymous namespace at
// the top of this class is used to unpack a tuple and call a function (the
// archive/unarchive function) on each of its elements. Thanks to this
// StackOverflow answer for details on how to unpack a tuple:
//  * https://stackoverflow.com/a/16387374/986991

#ifndef INCLUDE_TUPLE_HPP_
#define INCLUDE_TUPLE_HPP_

#include "../binary_output.hpp"
#include "../binary_input.hpp"

// Store tuple unpacking code in an anonymous namespace so it is local to
// the tuple class for now.
namespace {
// Used to hold a sequence of numbers at compile time.
template<std::size_t... Nums>
struct sequence {};

// Recursive case to continue sequence generation.
template<std::size_t N, std::size_t... Nums>
struct generate_sequence : generate_sequence<N - 1, N - 1, Nums...> {};

// Base case for generated sequence.
template<std::size_t... Nums>
struct generate_sequence<0, Nums...> : sequence<Nums...> {};

// Accepts an object, a functor, an Archive, and a variable sized sequence
// of ascending numbers (should be a `generate_sequence` struct). Using an
// initializer list to ensure ordering, the sequence is used to call `get`
// on each element in the tuple. By expanding the sequence using ..., one
// call to the functor is made for each element in the tuple.
template<typename T, typename F, typename Archive, std::size_t... Nums>
void for_each(T&& t, F f, Archive& oa, sequence<Nums...>) {
  auto _ = { (f(oa, std::get<Nums>(t)), 0)... };
  // "Use" the variable to avoid unused variable warnings from the compiler.
  (void) _;
}

// Accepts a tuple with an arbitrary number of values, an instance of a
// functor (a class which overloads operator()), and an Archive. Creates
// a sequence of ascending values from 0 to the size of the passed in tuple.
// Using this sequence, calls a helper function to look at each element in
// the tuple.
template<typename... Types, typename F, typename Archive>
void tuple_for_each(std::tuple<Types...>& t, F f, Archive& oa) {
  for_each(t, f, oa, generate_sequence<sizeof...(Types)>());
}

// Class used as a wrapper to handle operations on individual elements
// of a tuple.
struct TupleFunctor {
  // Overload the function call operator to handle serialization and
  // deserialization (the Archive type is generic) of individual elements
  // of a tuple.
  template<typename Archive, typename T>
  void operator()(Archive& ar, T&& t) {
    ar(t);
  }
};
}

namespace draft {
namespace binary {

// Save the tuple by writing each of its elements. Because a tuple can hold
// an arbitrary number of elements with arbitrary types, special code must
// be used to iterate over the types at compile time to ensure they are
// serializable.
template<typename... Types>
void Save(OutputArchive&oa, std::tuple<Types...>& tuple) {
  tuple_for_each(tuple, TupleFunctor(), oa);
}

// Load the tuple by passing each element to the input archive.
template<typename... Types>
void Load(binary::InputArchive& ia, std::tuple<Types...>& tuple) {
  tuple_for_each(tuple, TupleFunctor(), ia);
}

}  // namespace binary
}  // namespace draft

#endif  // INCLUDE_TUPLE_HPP_
