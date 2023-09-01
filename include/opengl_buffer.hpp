#pragma once

#include "opengl_object.hpp"

template <class T, int BufferKind>
class OpenGLBuffer : public OpenGLObject
{
public:
    OpenGLBuffer(std::size_t count, const T *data)
    {
        glGenBuffers(1, &handle_);
        set_data(count, data);
    }

    ~OpenGLBuffer()
    {
        glDeleteBuffers(1, &handle_);
    }

    void set_data(std::size_t count, const T *data)
    {
        bind();
        glBufferData(BufferKind, count * sizeof(T), data, GL_STATIC_DRAW);
        unbind();
    }

    void bind() const
    {
        glBindBuffer(BufferKind, handle_);
    }

    void unbind() const
    {
        glBindBuffer(BufferKind, 0);
    }
};
