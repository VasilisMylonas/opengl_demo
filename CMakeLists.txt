cmake_minimum_required(VERSION 3.10)
project(opengl_demo CXX)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(opengl_demo ${SOURCES})
target_include_directories(opengl_demo PUBLIC include)
target_link_libraries(opengl_demo PUBLIC glfw GL GLEW)
target_compile_features(opengl_demo PUBLIC cxx_std_20)
target_compile_options(opengl_demo PUBLIC -Wall -Wextra -Wconversion -Werror -Wpedantic)
