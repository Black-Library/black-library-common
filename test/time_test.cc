/**
 * time_test.cc
 */

#include <catch2/catch_test_macros.hpp>

#include <TimeOperations.h>

namespace black_library {

namespace core {

namespace common {

TEST_CASE( "GetGUITimeString generic tests (pass)", "[single-file]" )
{
    std::time_t test_time_0 = ParseTimet("01/02/2003 7:08:09 PM", "%m/%d/%Y %I:%M:%S %p");
    REQUIRE( GetGUITimeString(test_time_0) == "" );
}

// TEST_CASE( "GetISOTimeString generic tests (pass)", "[single-file]" )
// {
//     REQUIRE( GetISOTimeString(test_time_0) == "" );
// }

TEST_CASE( "GetUnixTime generic tests (pass)", "[single-file]" )
{
    REQUIRE( GetUnixTime() );
}

// TEST_CASE( "ParseTimet generic tests (pass)", "[single-file]" )
// {
//     time_t test_time_0 = GetUnixTime();
    
//     REQUIRE( ParseTimet("", "%m/%d/%Y %I:%M:%S %p") == "" );
// }


} // namespace common
} // namespace core
} // namespace black_library
