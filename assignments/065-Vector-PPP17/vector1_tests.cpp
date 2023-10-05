// tests for a very simplified vector of doubles
#include <catch2/catch_test_macros.hpp>
#include "vector1.hpp"

//------------------------------------------------------------------------------

TEST_CASE( "vector size operations", "[vector1]" ) {
    vector1 v1(1);
    REQUIRE( v1.size() == 1);
    vector1 v5(5);
    REQUIRE( v5.size() == 5);
}

TEST_CASE( "vector value operations", "[vector1]" ) {
    vector1 v(5);
    for (int i=0; i<v.size(); ++i) {
        v.set(i,1.1*i);
    }
    REQUIRE( v.get(0) == 0);
    REQUIRE( v.get(1) == 1.1);
    REQUIRE( v.get(2) == 2.2);
    REQUIRE( v.get(4) == 4.4);
}
