#pragma once

#include <string>
#include "opengl_object.hpp"

class Shader : public OpenGLObject
{
public:
    Shader(const std::string &fragment_source, const std::string &vertex_source)
    {
        GLuint fs = create_shader(GL_FRAGMENT_SHADER, fragment_source.c_str());
        GLuint vs = create_shader(GL_VERTEX_SHADER, vertex_source.c_str());

        handle_ = glCreateProgram();
        glAttachShader(handle_, fs);
        glAttachShader(handle_, vs);
        glLinkProgram(handle_);
    }

    ~Shader()
    {
        glDeleteShader(handle_);
    }

    bool valid()
    {
        glValidateProgram(handle_);

        int status;
        glGetProgramiv(handle_, GL_VALIDATE_STATUS, &status);
        return static_cast<bool>(status);
    }

private:
    GLuint create_shader(GLuint type, const char *source) const
    {
        GLuint id = glCreateShader(type);
        glShaderSource(id, 1, &source, nullptr);
        glCompileShader(id);
        return id;
    }
};