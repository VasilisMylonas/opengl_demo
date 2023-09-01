#pragma once

#include <string_view>

#include "opengl_object.hpp"

class Shader : public OpenGLObject
{
public:
    Shader(std::string_view fragment_source, std::string_view vertex_source)
    {
        GLuint fs = create_shader(GL_FRAGMENT_SHADER, fragment_source);
        GLuint vs = create_shader(GL_VERTEX_SHADER, vertex_source);

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
    static GLuint create_shader(GLuint type, std::string_view source)
    {
        const char *source_array[1] = {source.data()};
        GLsizei length_array[1] = {static_cast<GLsizei>(source.size())};

        GLuint id = glCreateShader(type);
        glShaderSource(id, 1, source_array, length_array);
        glCompileShader(id);
        return id;
    }
};