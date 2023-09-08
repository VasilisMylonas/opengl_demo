cmake_minimum_required(VERSION 3.10)
project(notagame CXX)

file(GLOB SRC src/*.cpp src/gl/*.cpp)

add_executable(notagame ${SRC})
target_include_directories(notagame PUBLIC include)
target_link_libraries(notagame PUBLIC glfw GL GLEW)
target_compile_features(notagame PUBLIC cxx_std_17)
target_compile_options(notagame PUBLIC -Wall -Wextra -Wconversion -Werror )#-Wpedantic)
