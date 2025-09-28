#pragma once

#include <GL/glew.h>
#include <iostream>
#include <string_view>

#define GL_CALL(function)                                                                          \
    gl::clear_error();                                                                             \
    function;                                                                                      \
    gl::check_error(__FILE__, __LINE__, __func__)

namespace gl
{

inline void clear_error()
{
    while (glGetError() != GL_NO_ERROR)
        ;
}

inline void check_error(std::string_view file, int line, std::string_view func)
{
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        std::cerr << "OpenGL error at " << file << ":" << line << " in " << func << "() " << error
                  << std::endl;
    }
}
} // namespace gl
