#pragma once

#include "gl/object.hpp"

#include <array>

namespace gl
{
    class Buffer : public Object
    {
    public:
        friend class VertexArray;

        enum class Usage
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

        enum class Target
        {
            INDEX = GL_ELEMENT_ARRAY_BUFFER,
            ARRAY = GL_ARRAY_BUFFER,
            TEXTURE = GL_TEXTURE_BUFFER,
        };

        enum class Access
        {
            READ_ONLY = GL_READ_ONLY,
            WRITE_ONLY = GL_WRITE_ONLY,
            READ_WRITE = GL_READ_WRITE,
        };

        Buffer(std::size_t size, Target target, Usage usage)
            : target_{target}
        {
            GL_CALL(glGenBuffers(1, &handle_));

            bind();
            GL_CALL(glBufferData(
                static_cast<GLenum>(target),
                static_cast<GLsizeiptr>(size),
                nullptr,
                static_cast<GLenum>(usage)));
            unbind();
        }

        Buffer(Buffer &&other)
            : Object(std::move(other)), target_{other.target_}
        {
        }

        Buffer &operator=(Buffer &&other)
        {
            target_ = other.target_;
            Object::operator=(std::move(other));
            return *this;
        }

        template <class T, std::size_t N>
        static Buffer from_array(const std::array<T, N> &data, Target target, Usage usage)
        {
            Buffer buffer{data.size() * sizeof(T), target, usage};
            buffer.data(0, data.size() * sizeof(T), data.data());
            return buffer;
        }

        ~Buffer()
        {
            GL_CALL(glDeleteBuffers(1, &handle_));
        }

        void *map(Access access)
        {
            bind();
            GL_CALL(void *ret = glMapBuffer(static_cast<GLenum>(target_), static_cast<GLenum>(access)));
            unbind();
            return ret;
        }

        bool unmap()
        {
            bind();
            GL_CALL(bool ret = glUnmapBuffer(static_cast<GLenum>(target_)));
            unbind();
            return ret;
        }

        // TODO: get buffer data?

        Buffer &data(std::ptrdiff_t offset, std::size_t size, const void *data)
        {
            bind();
            GL_CALL(glBufferSubData(
                static_cast<GLenum>(target_),
                static_cast<GLintptr>(offset),
                static_cast<GLsizeiptr>(size),
                data));
            unbind();
            return *this;
        }

    protected:
        void bind() const
        {
            GL_CALL(glBindBuffer(static_cast<GLenum>(target_), handle_));
        }

        void unbind() const
        {
            GL_CALL(glBindBuffer(static_cast<GLenum>(target_), 0));
        }

    private:
        Target target_;
    };
} // namespace gl