# draft tests

Draft uses the [Catch2](https://github.com/catchorg/Catch2) test framework. It assumes Catch has been installed in a system-wide location.

## Run Tests

Run `make test` to create a test binary `bin/tests`.

## Install Catch

### Mac

`brew install catch2`

### Linux

Download the [single include header](https://github.com/catchorg/Catch2/blob/master/single_include/catch2/catch.hpp) to `/usr/local/include`.

### Alternative

Alternatively, download the [single include header](https://github.com/catchorg/Catch2/blob/master/single_include/catch2/catch.hpp) and update the `Makefile` build command with `-I path/to/catch.hpp` to tell the compiler where to find Catch.

## Testing Methodology

Unit tests are written to test the serialization / deserialization process. If a type can be serialized and deserialized and return the same result, the test is assumed to be successful.

The file `tests.cpp` `include`s each test file and only this file is compiled instead of compiling each test file separately. This is not ideal because it means any time a test is changed the entire test suite has to be recompiled. However, because draft is a header-only library, compiling each test separately means the object files cannot be linked -- the linker would find multiple definitions of each symbol defined in draft when linking each tests object file. See [#5](https://github.com/LukasJoswiak/draft/issues/5) for progress on solving this issue.
