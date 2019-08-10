// Since draft is a header-only library, including draft in each test
// file causes a linker error when combining each test's object file.
// The solution is to include each test in a single file and compile
// this file, which prevents multiple includes of the draft library.
// This is not a great solution, because each time any test is changed,
// all tests have to be recompiled, but it is an OK solution for now.
#include "basic_types.hpp"
#include "basic_class.hpp"
#include "string.hpp"
#include "pair.hpp"
#include "tuple.hpp"
