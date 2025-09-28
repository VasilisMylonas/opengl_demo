#pragma once

#include "gl/texture.hpp"
#include "gl/vertex_array.hpp"

namespace gl
{

inline const char* version()
{
    return reinterpret_cast<const char*>(glGetString(GL_VERSION));
}

inline const char* name()
{
    return reinterpret_cast<const char*>(glGetString(GL_RENDERER));
}

inline void enable_blending()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

inline void draw(const vertex_array& vao, std::size_t count)
{
    vao.bind();
    GL_CALL(glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(count), GL_UNSIGNED_INT, nullptr));
    vao.unbind();
}

inline void draw_texture(const texture& texture, const vertex_array& vao, std::size_t count)
{
    // TODO: active texture
    texture.select();
    texture.bind();
    draw(vao, count);
    texture.unbind();
}

} // namespace gl
