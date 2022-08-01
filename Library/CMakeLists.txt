set(TARGET_NAME boggle_lib)

add_library(
    ${TARGET_NAME}
    STATIC
    Dictionary.cpp
)

target_link_libraries(
    ${TARGET_NAME}
    Boost::Boost
)

target_include_directories(
    ${TARGET_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

