#pragma once

#include "gl/buffer.hpp"
#include "gl/layout.hpp"

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

        VertexArray(VertexArray &&other) : Object(std::move(other))
        {
        }

        VertexArray &operator=(VertexArray &&other)
        {
            Object::operator=(std::move(other));
            return *this;
        }

        VertexArray &buffer(const Buffer &vbo, const Layout &layout)
        {
            bind();
            vbo.bind();

            auto stride = static_cast<GLuint>(layout.stride());
            std::size_t offset = 0;

            for (std::size_t i = 0; i < layout.count(); i++)
            {
                auto index = static_cast<GLuint>(i);
                GL_CALL(glEnableVertexArrayAttrib(handle_, index));
                GL_CALL(glVertexAttribPointer(
                    index,
                    layout[i].count,
                    layout[i].type,
                    layout[i].normalized,
                    stride,
                    reinterpret_cast<void *>(offset)));
                offset += layout[i].count * layout[i].size;
            }

            vbo.unbind();
            unbind();
            return *this;
        }

        VertexArray &draw(std::size_t count)
        {
            draw(0, count);
            return *this;
        }

        VertexArray &draw(std::size_t first, std::size_t count)
        {
            bind();
            // TODO: draw type
            GL_CALL(glDrawArrays(GL_TRIANGLES, static_cast<GLint>(first), static_cast<GLsizei>(count)));
            unbind();
            return *this;
        }

        const VertexArray &draw(std::size_t count) const
        {
            draw(0, count);
            return *this;
        }

        const VertexArray &draw(std::size_t first, std::size_t count) const
        {
            bind();
            GL_CALL(glDrawArrays(GL_TRIANGLES, static_cast<GLint>(first), static_cast<GLsizei>(count)));
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
