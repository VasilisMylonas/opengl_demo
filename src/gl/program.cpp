#include "gl/program.hpp"

namespace gl
{

Program::Program() : Object{0}
{
    GL_CALL(handle_ = glCreateProgram());
}

Program::~Program()
{
    GL_CALL(glDeleteProgram(handle_));
}

Program::Program(Program&& other) : Object{std::move(other)}
{
}

Program& Program::operator=(Program&& other)
{
    Object::operator=(std::move(other));
    return *this;
}

bool Program::valid() const
{
    GL_CALL(glValidateProgram(handle_));

    int status;
    GL_CALL(glGetProgramiv(handle_, GL_VALIDATE_STATUS, &status));
    return status;
}

Program& Program::attach(const Shader& shader)
{
    GL_CALL(glAttachShader(handle_, shader.handle()));
    return *this;
}

Program& Program::detach(const Shader& shader)
{
    GL_CALL(glDetachShader(handle_, shader.handle()));
    return *this;
}

Program& Program::link()
{
    GL_CALL(glLinkProgram(handle_));
    return *this;
}

Program& Program::use()
{
    GL_CALL(glUseProgram(handle_));
    return *this;
}

std::optional<Uniform> Program::uniform(const std::string& name) const
{
    GL_CALL(int location = glGetUniformLocation(handle_, name.c_str()));

    if (location == -1)
    {
        return {};
    }

    return Uniform{handle_, location};
}

} // namespace gl
