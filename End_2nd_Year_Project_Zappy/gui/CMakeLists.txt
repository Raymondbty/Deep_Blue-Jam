cmake_minimum_required(VERSION 3.17)
project(zappy_gui)

file(GLOB SOURCES "src/*.cpp")
add_executable(zappy_gui ${SOURCES})

set(CMAKE_BUILD_TYPE Release)

include(../cmake/Findraylib.cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(GRAPHICS GRAPHICS_API_OPENGL_43)
set(OpenGL_GL_PREFERENCE GLVND)
# add valgrind compilation flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")

target_include_directories(zappy_gui PUBLIC ${EXTRA_INCLUDES})
target_link_libraries(zappy_gui PUBLIC raylib)

add_custom_command(TARGET zappy_gui POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:zappy_gui> ${CMAKE_SOURCE_DIR}
)