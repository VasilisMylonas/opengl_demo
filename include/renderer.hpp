#pragma once

#include <cstddef>

#include "vertex.hpp"
#include "gl/buffer.hpp"

namespace gl
{
    using VertexBuffer = gl::Buffer<Vertex, gl::BufferTarget::ARRAY>;
    using IndexBuffer = gl::Buffer<unsigned int, gl::BufferTarget::INDEX>;

    class VertexArray : public gl::Object
    {
    public:
        VertexArray()
        {
            GL_CALL(glGenVertexArrays(1, &handle_));
        }

        void buffers(const VertexBuffer &vbo, const IndexBuffer &ibo)
        {
            bind();
            vbo.bind();
            ibo.bind();

            // See vertex.hpp
            GL_CALL(glEnableVertexArrayAttrib(handle_, 0));
            GL_CALL(glEnableVertexArrayAttrib(handle_, 1));
            GL_CALL(glEnableVertexArrayAttrib(handle_, 2));

            GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, position))));
            GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, normal))));
            GL_CALL(glVertexAttribPointer(2, 4, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, color))));

            unbind();
            vbo.unbind();
            ibo.unbind();
        }

        ~VertexArray()
        {
            GL_CALL(glDeleteVertexArrays(1, &handle_));
        }

        void draw(std::size_t count)
        {
            bind();
            GL_CALL(glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(count), GL_UNSIGNED_INT, nullptr));
            unbind();
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
    };

} // namespace gl