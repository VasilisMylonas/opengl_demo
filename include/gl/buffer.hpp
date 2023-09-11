#pragma once

#include "gl/object.hpp"

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

template <typename T, BufferTarget U>
class Buffer : public Object
{
public:
    friend class VertexArray;

    template <typename TOther, BufferTarget UOther>
    explicit Buffer(Buffer<TOther, UOther>&& other) : Object{std::move(other)}
    {
    }

    Buffer(Buffer&& other) : Object{std::move(other)}
    {
    }

    Buffer& operator=(Buffer&& other)
    {
        this->~Buffer();
        Object::operator=(std::move(other));
        return *this;
    }

    Buffer(std::size_t count, BufferUsage usage) : Object{0}
    {
        GL_CALL(glGenBuffers(1, &handle_));

        bind();
        GL_CALL(glBufferData(static_cast<GLenum>(U),
                             static_cast<GLsizeiptr>(count) * sizeof(T),
                             nullptr,
                             static_cast<GLenum>(usage)));
        unbind();
    }

    ~Buffer()
    {
        GL_CALL(glDeleteBuffers(1, &handle_));
    }

    T* map(BufferAccess access)
    {
        bind();
        GL_CALL(T* ret = glMapBuffer(static_cast<GLenum>(U), static_cast<GLenum>(access)));
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

    void data(std::size_t count, const T* data, std::size_t dest_index = 0)
    {
        bind();
        GL_CALL(glBufferSubData(
            static_cast<GLenum>(U), dest_index * sizeof(T), count * sizeof(T), data));
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