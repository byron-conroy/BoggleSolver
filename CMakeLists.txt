project(BoggleSolver)
cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 17)
option(BUILD_TESTING "Whether or not automated tests are built" ON)

include(Dependencies/Conan.cmake)

find_package(Boost REQUIRED)

add_subdirectory(Library)
add_subdirectory(Application)

if(BUILD_TESTING)
    enable_testing()

    # Find the testing libraries
    find_package(Catch2 REQUIRED)
    find_package(trompeloeil REQUIRED)

    # Provides the 'catch_discover_tests' CMake command
    include(Catch)

    add_subdirectory(Tests)
endif()
