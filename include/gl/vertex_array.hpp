#pragma once

#include "gl/buffer.hpp"
#include "gl/vertex.hpp"

namespace gl
{
using VertexBuffer = gl::Buffer<Vertex, gl::BufferTarget::ARRAY>;
using IndexBuffer = gl::Buffer<unsigned int, gl::BufferTarget::INDEX>;

class VertexArray : public Object
{
public:
    VertexArray();
    ~VertexArray();

    VertexArray(VertexArray&& other);
    VertexArray& operator=(VertexArray&& other);

    VertexArray& buffers(const VertexBuffer& vbo, const IndexBuffer& ibo);
    void draw(std::size_t count);

protected:
    void bind() const;
    void unbind() const;
};

} // namespace gl