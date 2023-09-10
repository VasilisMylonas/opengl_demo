#include "gl/uniform.hpp"

namespace gl
{

void Uniform::set(const glm::vec1& vec)
{
    GL_CALL(glProgramUniform1f(program_, static_cast<int>(handle_), vec.x));
}

void Uniform::set(const glm::vec2& vec)
{
    GL_CALL(glProgramUniform2f(program_, static_cast<int>(handle_), vec.x, vec.y));
}

void Uniform::set(const glm::vec3& vec)
{
    GL_CALL(glProgramUniform3f(program_, static_cast<int>(handle_), vec.x, vec.y, vec.z));
}

void Uniform::set(const glm::vec4& vec)
{
    GL_CALL(glProgramUniform4f(program_, static_cast<int>(handle_), vec.x, vec.y, vec.z, vec.w));
}

void Uniform::set(int value)
{
    GL_CALL(glProgramUniform1i(program_, static_cast<int>(handle_), value));
}

void Uniform::set(std::size_t count, const int* values)
{
    GL_CALL(glProgramUniform1iv(
        program_, static_cast<int>(handle_), static_cast<GLsizei>(count), values));
}

Uniform::Uniform(Uniform&& other) : Object{std::move(other)}
{
    program_ = other.program_;
}

Uniform& Uniform::operator=(Uniform&& other)
{
    Object::operator=(std::move(other));
    program_ = other.program_;
    return *this;
}

Uniform::Uniform(unsigned int program, unsigned int handle) : Object{handle}
{
    program_ = program;
}

} // namespace gl
