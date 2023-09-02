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
            Array = GL_ARRAY_BUFFER,
            Texture = GL_TEXTURE_BUFFER,
        };

        Buffer()
        {
            GL_CALL(glGenBuffers(1, &handle_));
        }

        ~Buffer()
        {
            GL_CALL(glDeleteBuffers(1, &handle_));
        }

        Buffer &size(std::size_t size)
        {
            size_ = size;
            return *this;
        }

        std::size_t size() const
        {
            return size_;
        }

        Buffer &usage(Usage usage)
        {
            usage_ = usage;
            return *this;
        }

        Usage usage() const
        {
            return usage_;
        }

        Buffer &target(Target target)
        {
            target_ = target;
            return *this;
        }

        Target target() const
        {
            return target_;
        }

        Buffer &bind()
        {
            GL_CALL(glBindBuffer(static_cast<GLenum>(target_), handle_));
            return *this;
        }

        Buffer &unbind()
        {
            GL_CALL(glBindBuffer(static_cast<GLenum>(target_), 0));
            return *this;
        }

        const Buffer &bind() const
        {
            GL_CALL(glBindBuffer(static_cast<GLenum>(target_), handle_));
            return *this;
        }

        const Buffer &unbind() const
        {
            GL_CALL(glBindBuffer(static_cast<GLenum>(target_), 0));
            return *this;
        }

        Buffer &data(const void *data)
        {
            bind();
            GL_CALL(glBufferData(
                static_cast<GLenum>(target_),
                static_cast<GLsizeiptr>(size_),
                data,
                static_cast<GLenum>(usage_)));
            unbind();
            return *this;
        }

        // TODO: get buffer data?

        Buffer &update(std::ptrdiff_t offset, std::size_t size, const void *data)
        {
            bind();
            glBufferSubData(
                static_cast<GLenum>(target_),
                static_cast<GLintptr>(offset),
                static_cast<GLsizeiptr>(size),
                data);
            unbind();
            return *this;
        }

    private:
        std::size_t size_{0};
        Usage usage_{Usage::STATIC_DRAW};
        Target target_{Target::Array};
    };
} // namespace gl