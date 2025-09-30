cmake_minimum_required(VERSION 3.10)
project(opengl_demo CXX)

set(OpenGL_GL_PREFERENCE GLVND) # Use modern OpenGL

file(GLOB SOURCES src/*.cpp)
file(GLOB IMGUI_SOURCES
    third_party/imgui/*.cpp
    third_party/imgui/backends/imgui_impl_glfw.cpp
    third_party/imgui/backends/imgui_impl_opengl3.cpp
)
file(GLOB IMGUI_FILE_DIALOG_SOURCES
    third_party/ImGuiFileDialog/*.cpp
)

add_subdirectory(third_party/glm)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

add_executable(opengl_demo ${SOURCES} ${IMGUI_SOURCES} ${IMGUI_FILE_DIALOG_SOURCES})
target_include_directories(opengl_demo PRIVATE
    include
    third_party/imgui
    third_party/imgui/backends
    third_party/ImGuiFileDialog
)
target_link_libraries(opengl_demo PRIVATE glfw OpenGL::GL GLEW::GLEW glm)
target_compile_features(opengl_demo PRIVATE cxx_std_20)
target_compile_options(opengl_demo PRIVATE -Wall -Wextra -Wconversion)
