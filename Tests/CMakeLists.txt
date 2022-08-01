set(TARGET_NAME tests)

add_executable (
    ${TARGET_NAME}
    TestsMain.cpp
    UnitTests/DictionaryT.cpp
)

target_link_libraries(
    ${TARGET_NAME}
    Catch2::Catch2
    boggle_lib
)

catch_discover_tests(${TARGET_NAME})
