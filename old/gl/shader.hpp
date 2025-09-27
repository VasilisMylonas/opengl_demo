#pragma once

#include "gl/object.hpp"

#include <string>
#include <string_view>

namespace gl
{

class Shader : public Object
{
public:
    enum class Type
    {
        fragment = GL_FRAGMENT_SHADER,
        vertex = GL_VERTEX_SHADER,
    };

    Shader(Type type);
    ~Shader();
    Shader(Shader&& other);
    Shader& operator=(Shader&& other);

    std::string_view source() const;

    Shader& source_path(const std::string& path);
    Shader& source(std::string_view source);
    Shader& compile();

private:
    std::string source_;
};

} // namespace gl
