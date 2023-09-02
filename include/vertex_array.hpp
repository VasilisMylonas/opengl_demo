#pragma once

#include "buffer.hpp"
#include "vertex_layout.hpp"

namespace gl
{
    class VertexArray : public Object
    {
    public:
        VertexArray()
        {
            GL_CALL(glGenVertexArrays(1, &handle_));
        }

        // VertexArray(const Buffer &vbo, const VertexLayout &layout) : VertexArray()
        // {
        //     set_buffer(vbo, layout);
        // }

        // void set_buffer(const Buffer &vbo, const VertexLayout &layout, const Buffer &ibo)
        // {
        //     bind();
        //     ibo.bind();
        //     set_buffer(vbo, layout);
        //     unbind();
        //     ibo.unbind();
        // }

        // void set_buffer(const Buffer &vbo, const VertexLayout &layout)
        // {
        //     bind();
        //     vbo.bind();

        //     const auto &attr = layout.attributes();
        //     auto stride = static_cast<GLuint>(layout.stride());
        //     std::size_t offset = 0;

        //     for (std::size_t i = 0; i < attr.size(); i++)
        //     {
        //         auto index = static_cast<GLuint>(i);
        //         glEnableVertexArrayAttrib(handle_, index);
        //         glVertexAttribPointer(
        //             index,
        //             attr[i].count,
        //             attr[i].type,
        //             attr[i].normalized,
        //             stride,
        //             reinterpret_cast<void *>(offset));
        //         offset += attr[i].count * attr[i].size;
        //     }

        //     vbo.unbind();
        //     unbind();
        // }

        ~VertexArray()
        {
            GL_CALL(glDeleteVertexArrays(1, &handle_));
        }

        void bind() const
        {
            GL_CALL(glBindVertexArray(handle_));
        }

        void unbind() const
        {
            GL_CALL(glBindVertexArray(0));
        }
    };

} // namespace gl