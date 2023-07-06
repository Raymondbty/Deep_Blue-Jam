project(raytracer)
cmake_minimum_required(VERSION 3.0)
file(GLOB SOURCES "src/*.cpp")

add_executable(raytracer ${SOURCES})
add_compile_options(-Wall -Wextra -Werror -std=c++20)
target_include_directories(raytracer PUBLIC include)
target_link_libraries(raytracer config++)
add_custom_command(TARGET raytracer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:raytracer> ${CMAKE_SOURCE_DIR}
)
