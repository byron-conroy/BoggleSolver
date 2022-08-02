set(TARGET_NAME tests)

add_executable (
    ${TARGET_NAME}
    TestsMain.cpp
    UnitTests/SimpleDictionaryT.cpp
    UnitTests/GridT.cpp
    UnitTests/BoggleT.cpp
)

target_link_libraries(
    ${TARGET_NAME}
    Catch2::Catch2
    trompeloeil::trompeloeil
    boggle_lib
)

target_include_directories(
    ${TARGET_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

catch_discover_tests(${TARGET_NAME})
