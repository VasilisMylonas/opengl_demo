#pragma once

#include "gl/buffer.hpp"
#include "gl/vertex_layout.hpp"
#include <GL/gl.h>

namespace gl
{
class vertex_array
{
public:
    vertex_array()
    {
        GL_CALL(glGenVertexArrays(1, &handle_));
    }

    ~vertex_array()
    {
        if (handle_ != 0)
        {
            GL_CALL(glDeleteVertexArrays(1, &handle_));
        }
    }

    vertex_array(vertex_array&& other)
    {
        handle_ = other.handle_;
        other.handle_ = 0;
    }

    vertex_array& operator=(vertex_array&& other)
    {
        if (this == &other)
        {
            return *this;
        }

        GL_CALL(glDeleteVertexArrays(1, &handle_));
        handle_ = other.handle_;
        other.handle_ = 0;
        return *this;
    }

    vertex_array(const vertex_array&) = delete;
    vertex_array& operator=(const vertex_array&) = delete;

    template <typename VertexType, typename IndexType>
    void buffers(const vertex_buffer<VertexType>& vbo,
                 const index_buffer<IndexType>& ibo,
                 const vertex_layout& layout)
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

        ibo_size = ibo.size();
    }

    void draw(std::size_t count)
    {
        bind();
        // TODO: GL_UNSIGNED_INT, does it matter or is it just for indices?
        GL_CALL(glDrawElements(GL_TRIANGLES, static_cast<int>(count), GL_UNSIGNED_INT, nullptr));
        unbind();
    }

    void draw()
    {
        draw(ibo_size);
    }

private:
    void bind() const
    {
        GL_CALL(glBindVertexArray(handle_));
    }

    void unbind() const
    {
        GL_CALL(glBindVertexArray(0));
    }

    unsigned int handle_ = 0;
    std::size_t ibo_size = 0;
};

} // namespace gl
