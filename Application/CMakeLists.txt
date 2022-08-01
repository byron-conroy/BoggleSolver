set(TARGET_NAME boggle_game)

add_executable(
    ${TARGET_NAME}
    Main.cpp
)

target_link_libraries(
    ${TARGET_NAME}
    boggle_lib
)
