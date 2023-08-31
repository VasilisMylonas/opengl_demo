#pragma once

#include "opengl_object.hpp"
#include "vertex_buffer.hpp"

class VertexArray : public OpenGLObject
{
public:
    VertexArray(const VertexBuffer &buffer)
    {
        glGenVertexArrays(1, &handle_);

        bind();
        buffer.bind();

        // See Vertex.hpp
        glEnableVertexArrayAttrib(handle_, 0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        buffer.unbind();
        unbind();
    }

    ~VertexArray()
    {
        glDeleteVertexArrays(1, &handle_);
    }

    void bind()
    {
        glBindVertexArray(handle_);
    }

    void unbind()
    {
        glBindVertexArray(0);
    }
};
