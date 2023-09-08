#include "gl/shader.hpp"

#include "util.hpp"

namespace gl
{

Shader::Shader(Type type)
{
    GL_CALL(handle_ = glCreateShader(static_cast<GLenum>(type)));
}

Shader::~Shader()
{
    GL_CALL(glDeleteShader(handle_));
}

Shader::Shader(Shader&& other) : Object{std::move(other)}
{
}

Shader& Shader::operator=(Shader&& other)
{
    Object::operator=(std::move(other));
    return *this;
}

std::string_view Shader::source() const
{
    return source_;
}

Shader& Shader::source_path(const std::string& path)
{
    source_ = read_file(path);
    return *this;
}

Shader& Shader::source(std::string_view source)
{
    source_ = source;
    return *this;
}

Shader& Shader::compile()
{
    const char* source_array[1] = {source_.data()};
    GLsizei length_array[1] = {static_cast<GLsizei>(source_.size())};
    GL_CALL(glShaderSource(handle_, 1, source_array, length_array));
    GL_CALL(glCompileShader(handle_));
    return *this;
}

} // namespace gl