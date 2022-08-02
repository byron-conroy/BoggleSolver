project(BoggleSolver)
cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 17)
option(BUILD_TESTING "Whether or not automated tests are built" ON)

#CMake has a weird empty build type if you don't manually specify one
set(default_build_type "Debug")
if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
else()
    message(STATUS "Building in ${CMAKE_BUILD_TYPE} mode")
endif()

# Set binary output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

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
