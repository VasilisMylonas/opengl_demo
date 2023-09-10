#pragma once

#include "gl/object.hpp"

#include <string>

namespace gl
{

class Texture : public Object
{
public:
    friend class Renderer;

    Texture(unsigned int slot);
    ~Texture();
    Texture& source_path(const std::string& path);
    unsigned int slot() const;
    Texture& slot(unsigned int slot);

    // TODO: copy and move

protected:
    void bind() const;
    void unbind() const;
    void select() const;

private:
    unsigned int slot_;
};

} // namespace gl
