#pragma once

#include "opengl_object.hpp"
#include "vertex_array.hpp"
#include "shader.hpp"

class Renderer
{
public:
    static void use_shader(const Shader &shader)
    {
        glUseProgram(shader.handle());
    }

    static void draw(const VertexArray &vao, std::size_t first, std::size_t count)
    {
        vao.bind();
        glDrawArrays(GL_TRIANGLES, static_cast<GLint>(first), static_cast<GLsizei>(count));
        vao.unbind();
    }
};
