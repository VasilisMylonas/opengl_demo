#pragma once

#include "gl/errors.hpp"
#include <GL/gl.h>
#include <GL/glew.h>

namespace gl
{
enum class BufferUsage
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

enum class BufferTarget
{
    index = GL_ELEMENT_ARRAY_BUFFER,
    array = GL_ARRAY_BUFFER,
    texture = GL_TEXTURE_BUFFER,
};

enum class BufferAccess
{
    read_only = GL_READ_ONLY,
    write_only = GL_WRITE_ONLY,
    read_write = GL_READ_WRITE,
};

template <typename Type, BufferTarget Target>
class BasicBuffer
{
public:
    friend class VertexArray;

    BasicBuffer(BasicBuffer&& other)
    {
        handle_ = other.handle_;
        other.handle_ = 0;
    }

    BasicBuffer& operator=(BasicBuffer&& other)
    {
        this->~BasicBuffer();
        handle_ = other.handle_;
        other.handle_ = 0;
        return *this;
    }

    BasicBuffer(std::size_t count, BufferUsage usage)
    {
        GL_CALL(glGenBuffers(1, &handle_));
        bind();
        GL_CALL(glBufferData(static_cast<GLenum>(Target),
                             static_cast<GLsizeiptr>(count) * sizeof(Type),
                             nullptr,
                             static_cast<GLenum>(usage)));
        unbind();
    }

    ~BasicBuffer()
    {
        GL_CALL(glDeleteBuffers(1, &handle_));
    }

    Type* map(BufferAccess access)
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

    void data(std::size_t count, const Type* data, std::size_t dest_index = 0)
    {
        bind();
        GL_CALL(glBufferSubData(
            static_cast<GLenum>(Target), dest_index * sizeof(Type), count * sizeof(Type), data));
        unbind();
    }

protected:
    void bind() const
    {
        GL_CALL(glBindBuffer(static_cast<GLenum>(Target), handle_));
    }

    void unbind() const
    {
        GL_CALL(glBindBuffer(static_cast<GLenum>(Target), 0));
    }

private:
    GLuint handle_ = 0;
};

template <typename T>
using ArrayBuffer = BasicBuffer<T, BufferTarget::array>;

template <typename T>
using TextureBuffer = BasicBuffer<T, BufferTarget::texture>;

template <typename T>
using IndexBuffer = BasicBuffer<T, BufferTarget::index>;

} // namespace gl
