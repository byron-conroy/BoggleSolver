#define CATCH_CONFIG_RUNNER

#include <catch2/catch.hpp>

int main( int argc, char* argv[] )
{
    // Pre Test Logic
    int result = Catch::Session().run( argc, argv );
    // Post Test Logic

    return result;
}