#pragma once

#include "gl/buffer.hpp"
#include "gl/layout.hpp"

namespace gl
{
    enum class DrawMode
    {
        POINTS = GL_POINTS,
        LINES = GL_LINES,
        LINE_STRIP = GL_LINE_STRIP,
        LINE_LOOP = GL_LINE_LOOP,
        TRIANGLES = GL_TRIANGLES,
        TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
        TRIANGLE_FAN = GL_TRIANGLE_FAN,
    };

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

            std::size_t offset = 0;
            std::size_t stride = layout.stride();

            for (std::size_t i = 0; i < layout.count(); i++)
            {
                auto index = static_cast<GLuint>(i);
                GL_CALL(glEnableVertexArrayAttrib(handle_, index));
                GL_CALL(glVertexAttribPointer(
                    index,
                    layout[i].count,
                    layout[i].type,
                    layout[i].normalized,
                    static_cast<GLsizei>(stride),
                    reinterpret_cast<void *>(offset)));
                offset += layout[i].stride;
            }

            vbo.unbind();
            unbind();
            return *this;
        }

        VertexArray &draw_elements(DrawMode mode, std::size_t count, const Buffer &ibo)
        {
            bind();
            ibo.bind();
            GL_CALL(glDrawElements(static_cast<GLenum>(mode), static_cast<GLsizei>(count), GL_UNSIGNED_INT, nullptr));
            ibo.unbind();
            unbind();
            return *this;
        }

        const VertexArray &draw_elements(DrawMode mode, std::size_t count, const Buffer &ibo) const
        {
            bind();
            ibo.bind();
            GL_CALL(glDrawElements(static_cast<GLenum>(mode), static_cast<GLsizei>(count), GL_UNSIGNED_INT, nullptr));
            ibo.unbind();
            unbind();
            return *this;
        }

        VertexArray &draw(DrawMode mode, std::size_t count)
        {
            draw(mode, 0, count);
            return *this;
        }

        const VertexArray &draw(DrawMode mode, std::size_t count) const
        {
            draw(mode, 0, count);
            return *this;
        }

        VertexArray &draw(DrawMode mode, std::size_t first, std::size_t count)
        {
            bind();
            GL_CALL(glDrawArrays(static_cast<GLenum>(mode), static_cast<GLint>(first), static_cast<GLsizei>(count)));
            unbind();
            return *this;
        }

        const VertexArray &draw(DrawMode mode, std::size_t first, std::size_t count) const
        {
            bind();
            GL_CALL(glDrawArrays(static_cast<GLenum>(mode), static_cast<GLint>(first), static_cast<GLsizei>(count)));
            unbind();
            return *this;
        }

    protected:
        void
        bind() const
        {
            GL_CALL(glBindVertexArray(handle_));
        }

        void unbind() const
        {
            GL_CALL(glBindVertexArray(0));
        }
    };
} // namespace gl
