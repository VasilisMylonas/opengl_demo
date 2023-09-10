#include "gl/texture.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#pragma GCC diagnostic pop

namespace gl
{

Texture::Texture() : Object{0}
{
    GL_CALL(glGenTextures(1, &handle_));
}

void Texture::source_path(const std::string& path)
{
    int x, y, c;
    unsigned char* data = stbi_load(path.c_str(), &x, &y, &c, 4);

    bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, x, y, 0, GL_RGBA8, GL_UNSIGNED_BYTE, data);

    unbind();

    stbi_image_free(data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &handle_);
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, handle_);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

} // namespace gl
