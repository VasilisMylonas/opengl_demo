#pragma once

#include "opengl_buffer.hpp"
#include "vertex.hpp"

class VertexBuffer : public OpenGLBuffer<Vertex, GL_ARRAY_BUFFER>
{
public:
    VertexBuffer(std::size_t count, const Vertex *data) : OpenGLBuffer(count, data)
    {
    }
};
