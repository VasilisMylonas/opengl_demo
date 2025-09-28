#pragma once

#include "gl/errors.hpp"
#include <GL/gl.h>
#include <GL/glew.h>

namespace gl
{
enum class buffer_usage
{
    static_draw = GL_STATIC_DRAW,
    dynamic_draw = GL_DYNAMIC_DRAW,
    stream_draw = GL_STREAM_DRAW,
    static_read = GL_STATIC_READ,
    dynamic_read = GL_DYNAMIC_READ,
    stream_read = GL_STREAM_READ,
    static_copy = GL_STATIC_COPY,
    dynamic_copy = GL_DYNAMIC_COPY,
    stream_copy = GL_STREAM_COPY,
};

enum class buffer_target
{
    index = GL_ELEMENT_ARRAY_BUFFER,
    vertex = GL_ARRAY_BUFFER,
    texture = GL_TEXTURE_BUFFER,
};

enum class buffer_access
{
    read_only = GL_READ_ONLY,
    write_only = GL_WRITE_ONLY,
    read_write = GL_READ_WRITE,
};

template <typename Type, buffer_target Target>
class basic_buffer
{
public:
    friend class vertex_array;

    basic_buffer(basic_buffer&& other)
    {
        handle_ = other.handle_;
        other.handle_ = 0;
    }

    basic_buffer& operator=(basic_buffer&& other)
    {
        if (this == &other)
        {
            return *this;
        }

        this->~basic_buffer();
        handle_ = other.handle_;
        other.handle_ = 0;
        return *this;
    }

    basic_buffer(const basic_buffer&) = delete;
    basic_buffer& operator=(const basic_buffer&) = delete;

    basic_buffer()
    {
        GL_CALL(glGenBuffers(1, &handle_));
    }

    ~basic_buffer()
    {
        if (handle_ != 0)
        {
            GL_CALL(glDeleteBuffers(1, &handle_));
        }
    }

    Type* map(buffer_access access)
    {
        bind();
        GL_CALL(Type* ret = glMapBuffer(static_cast<GLenum>(Target), static_cast<GLenum>(access)));
        unbind();
        return ret;
    }

    bool unmap()
    {
        bind();
        GL_CALL(bool ret = glUnmapBuffer(static_cast<GLenum>(Target)));
        unbind();
        return ret;
    }

    void data(std::size_t count, const Type* data, buffer_usage usage)
    {
        bind();
        GL_CALL(glBufferData(static_cast<GLenum>(Target),
                             static_cast<GLsizeiptr>(count) * sizeof(Type),
                             data,
                             static_cast<GLenum>(usage)));
        unbind();
    }

    // TODO
    // void update(std::size_t count, const Type* data, std::size_t dest_index = 0)
    // {
    //     bind();
    //     GL_CALL(glBufferSubData(
    //         static_cast<GLenum>(Target), dest_index * sizeof(Type), count * sizeof(Type), data));
    //     unbind();
    // }

private:
    void bind() const
    {
        GL_CALL(glBindBuffer(static_cast<GLenum>(Target), handle_));
    }

    void unbind() const
    {
        GL_CALL(glBindBuffer(static_cast<GLenum>(Target), 0));
    }

    GLuint handle_ = 0;
};

template <typename T>
using vertex_buffer = basic_buffer<T, buffer_target::vertex>;

template <typename T>
using texture_buffer = basic_buffer<T, buffer_target::texture>;

template <typename T>
using index_buffer = basic_buffer<T, buffer_target::index>;

} // namespace gl
