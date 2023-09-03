#pragma once

#include "gl/buffer.hpp"
#include "gl/vertex_array.hpp"

class Renderer
{
public:
    static void draw_elements(const gl::VertexArray &vao, std::size_t count)
    {
        vao.bind();
        // see index_buffer.hpp
        GL_CALL(glDrawElements(GL_LINE_STRIP, static_cast<GLsizei>(count), GL_UNSIGNED_INT, nullptr));
        vao.unbind();
    }
};
