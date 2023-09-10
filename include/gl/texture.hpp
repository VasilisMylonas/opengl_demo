#pragma once

#include "gl/object.hpp"

#include <string>

namespace gl
{

class Texture : public Object
{
public:
    friend class Renderer;

    Texture();
    ~Texture();
    void source_path(const std::string& path);

protected:
    void bind() const;
    void unbind() const;
};

} // namespace gl
