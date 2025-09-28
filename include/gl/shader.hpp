#pragma once

#include "gl/errors.hpp"
#include <GL/glew.h>
#include <string>

namespace gl
{
enum class shader_type
{
    fragment = GL_FRAGMENT_SHADER,
    vertex = GL_VERTEX_SHADER,
};

class shader
{
public:
    friend class program;

    shader& operator=(const shader&) = delete;
    shader(const shader&) = delete;
    shader& operator=(shader&& other) = delete;
    shader(shader&& other) = delete;

    shader(shader_type type)
    {
        GL_CALL(handle_ = glCreateShader(static_cast<GLenum>(type)));
    }

    ~shader()
    {
        GL_CALL(glDeleteShader(handle_));
    }

    std::string_view source() const
    {
        return source_;
    }

    void set_source(std::string_view source)
    {
        source_ = source;
    }

    void compile()
    {
        const char* source_array[1] = {source_.data()};
        GLsizei length_array[1] = {static_cast<GLsizei>(source_.size())};
        GL_CALL(glShaderSource(handle_, 1, source_array, length_array));
        GL_CALL(glCompileShader(handle_));
    }

private:
    unsigned int handle_ = 0;
    std::string source_;
};

} // namespace gl
