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

As different types gain serialization support, tests will be added.
