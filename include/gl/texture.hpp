#pragma once

#include <cassert>
#include <string>

#include "gl/errors.hpp"
#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace gl
{

class Texture
{
public:
    friend class Renderer;

    Texture(unsigned int slot) : slot_{slot}
    {
        GL_CALL(glGenTextures(1, &handle_));
    }

    ~Texture()
    {
        GL_CALL(glDeleteTextures(1, &handle_));
    }

    Texture& source_path(const std::string& path)
    {
        stbi_set_flip_vertically_on_load_thread(true);

        int x, y, c;
        unsigned char* data = stbi_load(path.c_str(), &x, &y, &c, 4);

        assert(data != nullptr);

        select();
        bind();

        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

        GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));

        unbind();

        stbi_image_free(data);

        return *this;
    }

    unsigned int slot() const
    {
        return slot_;
    }

    Texture& slot(unsigned int slot)
    {
        slot_ = slot;
        return *this;
    }

protected:
    void bind() const
    {
        GL_CALL(glBindTexture(GL_TEXTURE_2D, handle_));
    }

    void unbind() const
    {
        GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
    }

    void select() const
    {
        GL_CALL(glActiveTexture(GL_TEXTURE0 + slot_));
    }

private:
    unsigned int slot_;
    unsigned int handle_ = 0;
};

} // namespace gl
