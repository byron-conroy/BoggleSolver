# The bulk of this Cmake Script is pulled directly from https://github.com/conan-io/cmake-conan

# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(
        DOWNLOAD
        "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
        "${CMAKE_BINARY_DIR}/conan.cmake"
        EXPECTED_HASH SHA256=5cdb3042632da3efff558924eecefd580a0e786863a857ca097c3d1d43df5dcd
        TLS_VERIFY ON
    )
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

if(WIN32)
    set(CONAN_FILE "${CMAKE_CURRENT_LIST_DIR}/Windows.txt")
else()
    set(CONAN_FILE "${CMAKE_CURRENT_LIST_DIR}/Linux.txt")
endif()

conan_cmake_autodetect(CONAN_SETTINGS)

conan_cmake_install(
    PATH_OR_REFERENCE ${CONAN_FILE}
    BUILD missing
    REMOTE conancenter
    SETTINGS ${CONAN_SETTINGS}
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
