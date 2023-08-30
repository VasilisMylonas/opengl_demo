cmake_minimum_required(VERSION 3.10)
project(notagame CXX)

file(READ shaders/fs.glsl FS)
file(READ shaders/vs.glsl VS)

add_executable(notagame src/main.cpp src/window.cpp src/application_base.cpp)
target_include_directories(notagame PUBLIC include)
target_link_libraries(notagame PUBLIC glfw GL GLEW)
target_include_directories(notagame PUBLIC ${CMAKE_BINARY_DIR})
target_compile_features(notagame PUBLIC cxx_std_17)
configure_file(config.hpp.in config.hpp @ONLY)
target_compile_options(notagame PUBLIC -Wall -Wextra -Wconversion -Werror)