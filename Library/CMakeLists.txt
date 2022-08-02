set(TARGET_NAME boggle_lib)

add_library(
    ${TARGET_NAME}
    STATIC
    Dictionary/SimpleDictionary.cpp
    Dictionary/PredictiveDictionary.cpp
    Boggle/Game.cpp
    Boggle/Grid.cpp
    Boggle/UniformCharacterSequence.cpp
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

