# draft

[![build status](https://github.com/LukasJoswiak/draft/workflows/build/badge.svg)](https://github.com/LukasJoswiak/draft/actions)

Draft is a C++ serialization library, heavily inspired by [Boost.Serialization](http://www.boost.org/libs/serialization) and [cereal](https://uscilab.github.io/cereal/).

## Installation

Download the project and include `include/draft.hpp` in the file you want to add serialization too.

## Usage

*Draft is in early stage development and currently only supports serialization of:*

* `bool`
* `char`
* `int`
* `float`
* `double`
* `std::string`
* `std::array`
* `std::pair`
* `std::tuple`
* `std::map`
* `std::unordered_map`
* `std::unique_ptr`
* classes containing any of the above

### Serialization

Create an `OutputArchive` object with an output stream and pass the objects you want to serialize to it.

```cpp
#include <include/draft.hpp>

int main() {
  // Create an output stream to specify where the data will be written.
  std::ofstream stream("out", std::ios::binary);
  // Create the output archive.
  draft::binary::OutputArchive oa(stream);

  int x = 5;
  // Any variables you pass to oa will be serialized.
  oa(x);

  return 0;
}
```

### Deserialization

Create an `InputArchive` object with an input stream and pass objects to store the deserialized data in.

```cpp
#include <iostream>
#include <include/draft.hpp>

int main() {
  // Create an input stream to specify the location of the binary data.
  std::ifstream stream("out", std::ios::binary);
  // Create the input archive.
  draft::binary::InputArchive ia(stream);

  // Create variables to hold the deserialized values.
  int x;
  ia(x);

  std::cout << x << std::endl;  // Prints 5.

  return 0;
}
```

### Serialization and deserialization of classes

To serialize a class, add a `Serialize` function to it to tell draft which fields you want to serialize.

```cpp
#include <include/draft.hpp>

class Point {
 public:
  Point() {}
  Point(int x, int y) : x_(x), y_(y) {}

  // This function is used for both serialization and deserialization. Depending on whether
  // the class is being serialized on deserialized, Archive will be an OutputArchive or an
  // InputArchive, both of which overload the function call operator.
  template<typename Archive>
  void Serialize(Archive& ar) const {
    ar(x_, y_);
  }

 private:
  int x_;
  int y_;
};

int main() {
  {
    std::ofstream stream("out", std::ios::binary);
    draft::binary::OutputArchive oa(stream);

    Point p(1, 2);
    oa(p);
  }
  
  {
    std::ifstream stream("out", std::ios::binary);
    draft::binary::InputArchive ia(stream);

    Point p;
    ia(p);
    // p contains a point with x_ = 1, y_ = 2.
  }

  return 0;
}
```

## FAQ

### Why doesn't draft support serialization of raw pointers?

Raw pointers can point anywhere in memory. They can point to variables on the stack, the heap, or to read-only portions of memory such as where string literals are commonly stored. If raw pointers were serializable, memory would have to be allocated during the deserialization process to store the data pointed to by the pointer. This is not possible for all areas in memory. For data on the stack and heap, draft would likely write to different addresses than those used in the serialization process, losing determinism. In order to serialize pointers, use smart pointers.
