#pragma once

#include "gl/object.hpp"

namespace gl
{
    enum class BufferUsage
    {
        STATIC_DRAW = GL_STATIC_DRAW,
        DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
        STREAM_DRAW = GL_STREAM_DRAW,
        STATIC_READ = GL_STATIC_READ,
        DYNAMIC_READ = GL_DYNAMIC_READ,
        STREAM_READ = GL_STREAM_READ,
        STATIC_COPY = GL_STATIC_COPY,
        DYNAMIC_COPY = GL_DYNAMIC_COPY,
        STREAM_COPY = GL_STREAM_COPY,
    };

    enum class BufferTarget
    {
        INDEX = GL_ELEMENT_ARRAY_BUFFER,
        ARRAY = GL_ARRAY_BUFFER,
        TEXTURE = GL_TEXTURE_BUFFER,
    };

    enum class BufferAccess
    {
        READ_ONLY = GL_READ_ONLY,
        WRITE_ONLY = GL_WRITE_ONLY,
        READ_WRITE = GL_READ_WRITE,
    };

    template <class T, BufferTarget U>
    class Buffer : public Object
    {
    public:
        friend class VertexArray;

        template <class TOther, BufferTarget UOther>
        explicit Buffer(Buffer<TOther, UOther> &&other) : Object{std::move(other)}
        {
        }

        Buffer(Buffer &&other) : Object{std::move(other)}
        {
        }

        Buffer &operator=(Buffer &&other)
        {
            Object::operator=(std::move(other));
            return *this;
        }

        Buffer(std::size_t count, BufferUsage usage)
        {
            GL_CALL(glGenBuffers(1, &handle_));

            bind();
            GL_CALL(glBufferData(
                static_cast<GLenum>(U),
                static_cast<GLsizeiptr>(count) * sizeof(T),
                nullptr,
                static_cast<GLenum>(usage)));
            unbind();
        }

        ~Buffer()
        {
            GL_CALL(glDeleteBuffers(1, &handle_));
        }

        T *map(BufferAccess access)
        {
            bind();
            GL_CALL(T *ret = glMapBuffer(static_cast<GLenum>(U), static_cast<GLenum>(access)));
            unbind();
            return ret;
        }

        bool unmap()
        {
            bind();
            GL_CALL(bool ret = glUnmapBuffer(static_cast<GLenum>(U)));
            unbind();
            return ret;
        }

        void data(std::size_t count, const T *data, std::size_t dest_index = 0)
        {
            bind();
            GL_CALL(glBufferSubData(
                static_cast<GLenum>(U),
                dest_index * sizeof(T),
                count * sizeof(T),
                data));
            unbind();
        }

    protected:
        void bind() const
        {
            GL_CALL(glBindBuffer(static_cast<GLenum>(U), handle_));
        }

        void unbind() const
        {
            GL_CALL(glBindBuffer(static_cast<GLenum>(U), 0));
        }
    };
} // namespace gl