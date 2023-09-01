#pragma once

#include "opengl_object.hpp"
#include "vertex_buffer.hpp"
#include "index_buffer.hpp"

class VertexArray : public OpenGLObject
{
public:
    VertexArray(const VertexBuffer &vbo)
    {
        glGenVertexArrays(1, &handle_);

        bind();
        vbo.bind();

        // see vertex.hpp
        glEnableVertexArrayAttrib(handle_, 0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        unbind();
        vbo.unbind();
    }

    VertexArray(const VertexBuffer &vbo, const IndexBuffer &ibo)
    {
        glGenVertexArrays(1, &handle_);

        bind();
        vbo.bind();
        ibo.bind();

        // See Vertex.hpp
        glEnableVertexArrayAttrib(handle_, 0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        unbind();
        vbo.unbind();
        ibo.unbind();
    }

    ~VertexArray()
    {
        glDeleteVertexArrays(1, &handle_);
    }

    void bind() const
    {
        glBindVertexArray(handle_);
    }

    void unbind() const
    {
        glBindVertexArray(0);
    }
};
