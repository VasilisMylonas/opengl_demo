#pragma once

#include "gl/texture.hpp"
#include "gl/vertex_array.hpp"

namespace gl
{

class Renderer
{
public:
    static const char* version()
    {
        return reinterpret_cast<const char*>(glGetString(GL_VERSION));
    }

    static const char* name()
    {
        return reinterpret_cast<const char*>(glGetString(GL_RENDERER));
    }

    static void clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    static void enable_blending()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    static void draw_texture(const Texture& texture, const VertexArray& vao, std::size_t count)
    {
        // TODO: active texture
        texture.select();
        texture.bind();
        draw(vao, count);
        texture.unbind();
    }

    static void draw(const VertexArray& vao, std::size_t count)
    {
        vao.bind();
        GL_CALL(
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(count), GL_UNSIGNED_INT, nullptr));
        vao.unbind();
    }
};

} // namespace gl
