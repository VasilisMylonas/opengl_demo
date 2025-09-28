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

    shader& operator=(shader&& other)
    {
        if (this == &other)
        {
            return *this;
        }

        this->~shader();
        handle_ = other.handle_;
        source_ = std::move(other.source_);
        other.handle_ = 0;
        return *this;
    }

    shader(shader&& other)
    {
        handle_ = other.handle_;
        source_ = std::move(other.source_);
        other.handle_ = 0;
    }

    shader(shader_type type)
    {
        GL_CALL(handle_ = glCreateShader(static_cast<GLenum>(type)));
    }

    ~shader()
    {
        if (handle_ != 0)
        {
            GL_CALL(glDeleteShader(handle_));
        }
    }

    std::string_view source() const
    {
        return source_;
    }

    void set_source(std::string_view source)
    {
        source_ = source;
    }

    std::string info_log() const
    {
        std::string log;

        int length = 0;
        GL_CALL(glGetShaderiv(handle_, GL_INFO_LOG_LENGTH, &length));

        if (length > 0)
        {
            log.resize(length);
            GL_CALL(glGetShaderInfoLog(handle_, length, &length, log.data()));
        }

        return log;
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
