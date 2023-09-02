#pragma once

#include <GL/glew.h>

#include <cassert>
#include <iostream>

#define GL_CALL(function)                                                                     \
    function;                                                                                 \
    for (GLenum _gl_error = glGetError(); _gl_error != GL_NO_ERROR; _gl_error = glGetError()) \
    {                                                                                         \
        std::cerr << "OpenGL error at " << __FILE__ << ":" << __LINE__ << " in "              \
                  << __func__ << "() " << _gl_error << std::endl;                             \
        assert(false);                                                                        \
    }

namespace gl
{
    class Object
    {
    protected:
        GLuint handle_;
        Object() = default;
        Object(const Object &) = delete;
        Object &operator=(const Object &) = delete;

    public:
        Object(Object &&other)
        {
            handle_ = other.handle_;
            other.handle_ = 0;
        }

        Object &operator=(Object &&other)
        {
            handle_ = other.handle_;
            other.handle_ = 0;
            return *this;
        }

        GLuint handle() const
        {
            return handle_;
        }
    };

} // namespace gl