#pragma once

#include <GL/glew.h>

class OpenGLObject
{
protected:
    GLuint handle_;
    OpenGLObject() = default;
    OpenGLObject(const OpenGLObject &) = delete;
    OpenGLObject &operator=(const OpenGLObject &) = delete;

public:
    OpenGLObject(OpenGLObject &&other)
    {
        handle_ = other.handle_;
        other.handle_ = 0;
    }

    OpenGLObject &operator=(OpenGLObject &&other)
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
