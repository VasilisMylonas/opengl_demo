#pragma once

#include "opengl_buffer.hpp"

class IndexBuffer : public OpenGLBuffer<unsigned int, GL_ELEMENT_ARRAY_BUFFER>
{
public:
    IndexBuffer(std::size_t count, const unsigned int *data) : OpenGLBuffer(count, data)
    {
    }
};
