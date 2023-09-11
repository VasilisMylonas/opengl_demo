#pragma once

#include "gl/buffer.hpp"
#include "gl/vertex_layout.hpp"

namespace gl
{
template <typename VertexType>
using VertexBuffer = gl::Buffer<VertexType, gl::BufferTarget::array>;
using IndexBuffer = gl::Buffer<unsigned int, gl::BufferTarget::index>;

class VertexArray : public Object
{
public:
    friend class Renderer;

    VertexArray();
    ~VertexArray();

    VertexArray(VertexArray&& other);
    VertexArray& operator=(VertexArray&& other);

    template <typename VertexType>
    VertexArray&
    buffers(const VertexBuffer<VertexType>& vbo, const IndexBuffer& ibo, const VertexLayout& layout)
    {
        bind();
        vbo.bind();
        ibo.bind();

        for (unsigned i = 0; i < layout.size(); i++)
        {
            GL_CALL(glEnableVertexArrayAttrib(handle_, i));
            GL_CALL(glVertexAttribPointer(i,
                                          layout[i].type.first,
                                          layout[i].type.second,
                                          false,
                                          layout[i].stride,
                                          reinterpret_cast<void*>(layout[i].offset)));
        }

        unbind();
        vbo.unbind();
        ibo.unbind();
        return *this;
    }

protected:
    void bind() const;
    void unbind() const;
};

} // namespace gl