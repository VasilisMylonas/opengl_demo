#pragma once

#include "gl/buffer.hpp"
#include "gl/vertex_layout.hpp"

namespace gl
{
class VertexArray
{
public:
    VertexArray()
    {
        GL_CALL(glGenVertexArrays(1, &handle_));
    }

    ~VertexArray()
    {
        GL_CALL(glDeleteVertexArrays(1, &handle_));
    }

    VertexArray(VertexArray&& other)
    {
        handle_ = other.handle_;
        other.handle_ = 0;
    }

    VertexArray& operator=(VertexArray&& other)
    {
        if (this != &other)
        {
            GL_CALL(glDeleteVertexArrays(1, &handle_));
            handle_ = other.handle_;
            other.handle_ = 0;
        }
        return *this;
    }

    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;

    template <typename VertexType>
    void buffers(const ArrayBuffer<VertexType>& vbo,
                 const IndexBuffer<int>& ibo,
                 const VertexLayout& layout)
    {
        bind();
        vbo.bind();
        ibo.bind();

        for (unsigned i = 0; i < layout.size(); i++)
        {
            GL_CALL(glEnableVertexArrayAttrib(handle_, i));
            GL_CALL(glVertexAttribPointer(i,
                                          layout[i].type.first,
                                          layout[i].type.second,
                                          false,
                                          layout[i].stride,
                                          reinterpret_cast<void*>(layout[i].offset)));
        }

        unbind();
        vbo.unbind();
        ibo.unbind();
    }

protected:
    void bind() const
    {
        GL_CALL(glBindVertexArray(handle_));
    }

    void unbind() const
    {
        GL_CALL(glBindVertexArray(0));
    }

private:
    unsigned int handle_ = 0;
};

} // namespace gl
