#pragma once

#include "gl/shader.hpp"

namespace gl
{
    class Program : public Object
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

        bool valid() const
        {
            glValidateProgram(handle_);

            int status;
            glGetProgramiv(handle_, GL_VALIDATE_STATUS, &status);
            return static_cast<bool>(status);
        }

        Program &attach(const Shader &shader)
        {
            GL_CALL(glAttachShader(handle_, shader.handle()));
            return *this;
        }

        Program &detach(const Shader &shader)
        {
            GL_CALL(glDetachShader(handle_, shader.handle()));
            return *this;
        }

        Program &link()
        {
            GL_CALL(glLinkProgram(handle_));
            return *this;
        }

        Program &use()
        {
            GL_CALL(glUseProgram(handle_));
            return *this;
        }
    };
} // namespace gl
