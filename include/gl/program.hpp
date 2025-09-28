#pragma once

#include "gl/shader.hpp"
#include "gl/uniform.hpp"
#include <optional>
#include <string>

namespace gl
{

class program
{
public:
    program()
    {
        GL_CALL(handle_ = glCreateProgram());
    }

    ~program()
    {
        GL_CALL(glDeleteProgram(handle_));
    }

    program(const program&) = delete;
    program& operator=(const program&) = delete;
    program(program&&) = delete;
    program& operator=(program&&) = delete;

    std::optional<uniform> make_uniform(const std::string& name) const
    {
        int location = -1;
        GL_CALL(location = glGetUniformLocation(handle_, name.c_str()));
        if (location == -1)
        {
            return std::nullopt;
        }
        return uniform(handle_, location);
    }

    bool valid() const
    {
        GL_CALL(glValidateProgram(handle_));
        int status = 0;
        GL_CALL(glGetProgramiv(handle_, GL_VALIDATE_STATUS, &status));
        return status == GL_TRUE;
    }

    void attach(const shader& shader)
    {
        GL_CALL(glAttachShader(handle_, shader.handle_));
    }

    void detach(const shader& shader)
    {
        GL_CALL(glDetachShader(handle_, shader.handle_));
    }

    void link()
    {
        GL_CALL(glLinkProgram(handle_));
    }

    std::string info_log() const
    {
        std::string log;

        int length = 0;
        GL_CALL(glGetProgramiv(handle_, GL_INFO_LOG_LENGTH, &length));

        if (length > 0)
        {
            log.resize(length);
            GL_CALL(glGetProgramInfoLog(handle_, length, &length, log.data()));
        }

        return log;
    }

    void use() const
    {
        GL_CALL(glUseProgram(handle_));
    }

private:
    int handle_ = 0;
};
} // namespace gl
