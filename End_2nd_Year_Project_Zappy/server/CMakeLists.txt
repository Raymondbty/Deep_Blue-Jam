cmake_minimum_required(VERSION 3.17)
project(zappy_server)

file(GLOB SOURCES "main.c" "src/*.c" "utils/*.c" "src/commands/*.c" "src/commands/send_to_ai/*.c" "src/commands/send_to_gui/*.c")
add_executable(zappy_server ${SOURCES})

list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/include")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

target_include_directories(zappy_server PUBLIC ${EXTRA_INCLUDES})
target_link_libraries(zappy_server pthread)

add_custom_command(TARGET zappy_server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:zappy_server> ${CMAKE_SOURCE_DIR}
)
