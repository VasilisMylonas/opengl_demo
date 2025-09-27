cmake_minimum_required(VERSION 3.10)
project(opengl_demo CXX)

file(GLOB SOURCES src/*.cpp)
file(GLOB IMGUI_SOURCES
    third_party/imgui/*.cpp
    third_party/imgui/backends/imgui_impl_glfw.cpp
    third_party/imgui/backends/imgui_impl_opengl3.cpp
)
add_executable(opengl_demo ${SOURCES} ${IMGUI_SOURCES})

target_include_directories(opengl_demo PUBLIC
    include
    third_party/imgui
    third_party/imgui/backends
)
target_link_libraries(opengl_demo PUBLIC glfw GL GLEW)
target_compile_features(opengl_demo PUBLIC cxx_std_20)
target_compile_options(opengl_demo PUBLIC -Wall -Wextra -Wconversion)
