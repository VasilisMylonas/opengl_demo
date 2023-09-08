#pragma once

#include "gl/uniform.hpp"

#include <optional>
#include <string>
#include <string_view>

namespace gl
{

class Shader : public Object
{
public:
    enum class Type
    {
        FRAGMENT = GL_FRAGMENT_SHADER,
        VERTEX = GL_VERTEX_SHADER,
    };

    Shader(Type type);
    ~Shader();
    Shader(Shader&& other);
    Shader& operator=(Shader&& other);

    std::string_view source() const;

    Shader& source_path(const std::string& path);
    Shader& source(std::string_view source);
    Shader& compile();

    std::optional<Uniform> uniform(const std::string& name) const;

private:
    std::string source_;
};

} // namespace gl
