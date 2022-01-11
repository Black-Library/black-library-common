/**
 * log_test.cc
 */

#include <catch2/catch_test_macros.hpp>

#include <LogOperations.h>

namespace black_library {

namespace core {

namespace common {

TEST_CASE( "InitRotatingLogger generic tests (pass)", "[single-file]" )
{
    REQUIRE( InitRotatingLogger("test-logger", "/tmp/", true) == 0 );
    REQUIRE( InitRotatingLogger("test-logger", "/tmp/", true) == 0 );
}

} // namespace common
} // namespace core
} // namespace black_library
