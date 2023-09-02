#pragma once

#include <string_view>

#include "object.hpp"

namespace gl
{
    class Shader : public Object
    {
    public:
        enum class Type
        {
            FRAGMENT = GL_FRAGMENT_SHADER,
            VERTEX = GL_VERTEX_SHADER,
        };

        Shader(Type type)
        {
            GL_CALL(handle_ = glCreateShader(static_cast<GLenum>(type)));
        }

        ~Shader()
        {
            glDeleteShader(handle_);
        }

        // TODO: source() const

        Shader &set_source(std::string_view source)
        {
            const char *source_array[1] = {source.data()};
            GLsizei length_array[1] = {static_cast<GLsizei>(source.size())};
            GL_CALL(glShaderSource(handle_, 1, source_array, length_array));
            return *this;
        }

        Shader &compile()
        {
            GL_CALL(glCompileShader(handle_));
            return *this;
        }
    };
} // namespace gl