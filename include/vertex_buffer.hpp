#pragma once

#include "opengl_object.hpp"

class VertexBuffer : public OpenGLObject
{
public:
    VertexBuffer(std::size_t size, const void *data)
    {
        glGenBuffers(1, &handle_);
        bind();
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        unbind();
    }

    ~VertexBuffer()
    {
        glDeleteBuffers(1, &handle_);
    }

    void bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, handle_);
    }

    void unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
};
