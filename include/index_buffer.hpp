#pragma once

#include "opengl_object.hpp"

class IndexBuffer : public OpenGLObject
{
public:
    IndexBuffer(std::size_t count, const int *data)
    {
        glGenBuffers(1, &handle_);
        bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(int), data, GL_STATIC_DRAW);
        unbind();
    }

    ~IndexBuffer()
    {
        glDeleteBuffers(1, &handle_);
    }

    void bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle_);
    }

    void unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
};
