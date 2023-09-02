#pragma once

#include "gl/buffer.hpp"
#include "gl/vertex_layout.hpp"

namespace gl
{
    class VertexArray : public Object
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

        VertexArray &buffer(const Buffer &vbo, const VertexLayout &layout, const Buffer &ibo)
        {
            bind();
            ibo.bind();
            buffer(vbo, layout);
            unbind();
            ibo.unbind();
            return *this;
        }

        VertexArray &buffer(const Buffer &vbo, const VertexLayout &layout)
        {
            bind();
            vbo.bind();

            const auto &attr = layout.attributes();
            auto stride = static_cast<GLuint>(layout.stride());
            std::size_t offset = 0;

            for (std::size_t i = 0; i < attr.size(); i++)
            {
                auto index = static_cast<GLuint>(i);
                GL_CALL(glEnableVertexArrayAttrib(handle_, index));
                GL_CALL(glVertexAttribPointer(
                    index,
                    attr[i].count,
                    attr[i].type,
                    attr[i].normalized,
                    stride,
                    reinterpret_cast<void *>(offset)));
                offset += attr[i].count * attr[i].size;
            }

            vbo.unbind();
            unbind();
            return *this;
        }

        VertexArray &bind()
        {
            GL_CALL(glBindVertexArray(handle_));
            return *this;
        }

        VertexArray &unbind()
        {
            GL_CALL(glBindVertexArray(0));
            return *this;
        }

        const VertexArray &bind() const
        {
            GL_CALL(glBindVertexArray(handle_));
            return *this;
        }

        const VertexArray &unbind() const
        {
            GL_CALL(glBindVertexArray(0));
            return *this;
        }
    };

} // namespace gl