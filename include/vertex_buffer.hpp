#pragma once

#include "opengl_object.hpp"
#include "vertex.hpp"

class VertexBuffer : public OpenGLObject
{
public:
    VertexBuffer(std::size_t count, const Vertex *data)
    {
        glGenBuffers(1, &handle_);
        bind();
        glBufferData(GL_ARRAY_BUFFER, count * sizeof(Vertex), data, GL_STATIC_DRAW);
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
