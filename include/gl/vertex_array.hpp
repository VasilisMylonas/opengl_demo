#pragma once

#include "gl/buffer.hpp"
#include "gl/vertex.hpp"

namespace gl
{
using VertexBuffer = gl::Buffer<Vertex, gl::BufferTarget::array>;
using IndexBuffer = gl::Buffer<unsigned int, gl::BufferTarget::index>;

class VertexArray : public Object
{
public:
    friend class Renderer;

    VertexArray();
    ~VertexArray();

    VertexArray(VertexArray&& other);
    VertexArray& operator=(VertexArray&& other);

    VertexArray& buffers(const VertexBuffer& vbo, const IndexBuffer& ibo);

protected:
    void bind() const;
    void unbind() const;
};

} // namespace gl