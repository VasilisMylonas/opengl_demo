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
    this->~VertexArray();
    Object::operator=(std::move(other));
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
