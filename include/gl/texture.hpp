#pragma once

#include "gl/errors.hpp"
#include "stb_image.h"
#include <GL/glew.h>
#include <string>

namespace gl
{
class texture
{
public:
    texture()
    {
        glGenTextures(1, &handle_);
    }

    ~texture()
    {
        glDeleteTextures(1, &handle_);
    }

    texture(const texture&) = delete;
    texture& operator=(const texture&) = delete;

    texture(texture&& other)
    {
        handle_ = other.handle_;
        other.handle_ = 0;
    }

    texture& operator=(texture&& other)
    {
        if (this == &other)
        {
            return *this;
        }

        this->~texture();
        handle_ = other.handle_;
        other.handle_ = 0;
        return *this;
    }

    void load(const std::string& path)
    {
        bind();

        // Parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_set_flip_vertically_on_load(true);

        // Load image
        int width, height, channels;
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RGBA,
                     width,
                     height,
                     0,
                     channels == 4 ? GL_RGBA : GL_RGB,
                     GL_UNSIGNED_BYTE,
                     data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
        unbind();
    }

    void bind() const
    {
        GL_CALL(glBindTexture(GL_TEXTURE_2D, handle_));
    }

    void unbind() const
    {
        GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
    }

private:
    unsigned int handle_ = 0;
};
} // namespace gl
