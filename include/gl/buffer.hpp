#pragma once

#include "gl/object.hpp"

namespace gl
{
    class Buffer : public Object
    {
    public:
        enum class Usage : GLenum
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

        enum class Target : GLenum
        {
            Index = GL_ELEMENT_ARRAY_BUFFER,
            Vertex = GL_ARRAY_BUFFER,
            Texture = GL_TEXTURE_BUFFER,
        };

        Buffer(GLsizeiptr size, const void *data, Target target, Usage usage = Usage::STATIC_DRAW)
            : target_{target}
        {
            GL_CALL(glGenBuffers(1, &handle_));

            bind();
            GL_CALL(glBufferData(
                static_cast<GLenum>(target_),
                static_cast<GLsizeiptr>(size),
                data,
                static_cast<GLenum>(usage)));
            unbind();
        }

        ~Buffer()
        {
            GL_CALL(glDeleteBuffers(1, &handle_));
        }

        Target target() const
        {
            return target_;
        }

        void set_target(Target target)
        {
            target_ = target;
        }

        void bind() const
        {
            GL_CALL(glBindBuffer(static_cast<GLenum>(target_), handle_));
        }

        void unbind() const
        {
            GL_CALL(glBindBuffer(static_cast<GLenum>(target_), 0));
        }

        void data(std::ptrdiff_t offset, std::size_t size, void *data) const
        {
            bind();
            GL_CALL(glGetBufferSubData(
                static_cast<GLenum>(target_),
                static_cast<GLintptr>(offset),
                static_cast<GLsizeiptr>(size),
                data));
            unbind();
        }

        void set_data(std::ptrdiff_t offset, std::size_t size, const void *data)
        {
            bind();
            glBufferSubData(
                static_cast<GLenum>(target_),
                static_cast<GLintptr>(offset),
                static_cast<GLsizeiptr>(size),
                data);
            unbind();
        }

    private:
        Target target_;
    };
} // namespace gl