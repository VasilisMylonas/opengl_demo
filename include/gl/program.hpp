#pragma once

#include "gl/shader.hpp"
#include "gl/uniform.hpp"
#include <optional>

namespace gl
{
class Program
{
public:
    Program()
    {
        GL_CALL(handle_ = glCreateProgram());
    }

    ~Program()
    {
        GL_CALL(glDeleteProgram(handle_));
    }

    Program(const Program&) = delete;
    Program& operator=(const Program&) = delete;
    Program(Program&&) = delete;
    Program& operator=(Program&&) = delete;

    std::optional<Uniform> uniform(const std::string& name) const
    {
        int location = -1;
        GL_CALL(location = glGetUniformLocation(handle_, name.c_str()));
        if (location == -1)
        {
            return std::nullopt;
        }
        return Uniform(handle_, location);
    }

    bool valid() const
    {
        GL_CALL(glValidateProgram(handle_));
        int status = 0;
        GL_CALL(glGetProgramiv(handle_, GL_VALIDATE_STATUS, &status));
        return status == GL_TRUE;
    }

    void attach(const Shader& shader)
    {
        GL_CALL(glAttachShader(handle_, shader.handle_));
    }

    void detach(const Shader& shader)
    {
        GL_CALL(glDetachShader(handle_, shader.handle_));
    }

    void link()
    {
        GL_CALL(glLinkProgram(handle_));
    }

    void use() const
    {
        GL_CALL(glUseProgram(handle_));
    }

private:
    int handle_ = 0;
};
} // namespace gl
