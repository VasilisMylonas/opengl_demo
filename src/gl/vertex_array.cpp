#include "gl/vertex_array.hpp"

namespace gl
{
VertexArray::VertexArray() : Object{0}
{
    GL_CALL(glGenVertexArrays(1, &handle_));
}

VertexArray::VertexArray(VertexArray&& other) : Object{std::move(other)}
{
}

VertexArray& VertexArray::operator=(VertexArray&& other)
{
    Object::operator=(std::move(other));
    return *this;
}

VertexArray& VertexArray::buffers(const VertexBuffer& vbo, const IndexBuffer& ibo)
{
    bind();
    vbo.bind();
    ibo.bind();

    // See vertex.hpp
    // TODO: should be made configurable via layout class
    GL_CALL(glEnableVertexArrayAttrib(handle_, 0));
    GL_CALL(glEnableVertexArrayAttrib(handle_, 1));
    GL_CALL(glEnableVertexArrayAttrib(handle_, 2));
    GL_CALL(glEnableVertexArrayAttrib(handle_, 3));
    GL_CALL(glEnableVertexArrayAttrib(handle_, 4));

    GL_CALL(glVertexAttribPointer(0,
                                  3,
                                  GL_FLOAT,
                                  false,
                                  sizeof(Vertex),
                                  reinterpret_cast<void*>(offsetof(Vertex, position))));
    GL_CALL(glVertexAttribPointer(
        1, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal))));
    GL_CALL(glVertexAttribPointer(
        2, 4, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color))));
    GL_CALL(glVertexAttribPointer(
        3, 2, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, uv))));
    GL_CALL(glVertexAttribPointer(4,
                                  1,
                                  GL_UNSIGNED_INT,
                                  false,
                                  sizeof(Vertex),
                                  reinterpret_cast<void*>(offsetof(Vertex, texture))));

    unbind();
    vbo.unbind();
    ibo.unbind();
    return *this;
}

VertexArray::~VertexArray()
{
    GL_CALL(glDeleteVertexArrays(1, &handle_));
}

void VertexArray::bind() const
{
    GL_CALL(glBindVertexArray(handle_));
}

void VertexArray::unbind() const
{
    GL_CALL(glBindVertexArray(0));
}

} // namespace gl
