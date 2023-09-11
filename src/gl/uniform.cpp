#include "gl/uniform.hpp"

namespace gl
{

int Uniform::location() const
{
    return location_;
}

void Uniform::set(const glm::vec1& vec)
{
    GL_CALL(glProgramUniform1f(program_, location_, vec.x));
}

void Uniform::set(const glm::vec2& vec)
{
    GL_CALL(glProgramUniform2f(program_, location_, vec.x, vec.y));
}

void Uniform::set(const glm::vec3& vec)
{
    GL_CALL(glProgramUniform3f(program_, location_, vec.x, vec.y, vec.z));
}

void Uniform::set(const glm::vec4& vec)
{
    GL_CALL(glProgramUniform4f(program_, location_, vec.x, vec.y, vec.z, vec.w));
}

void Uniform::set(const glm::mat4& mat)
{
    GL_CALL(glProgramUniformMatrix4fv(program_, location_, 1, false, &mat[0][0]));
}

void Uniform::set(int value)
{
    GL_CALL(glProgramUniform1i(program_, location_, value));
}

void Uniform::set(std::size_t count, const int* values)
{
    GL_CALL(glProgramUniform1iv(program_, location_, static_cast<GLsizei>(count), values));
}

Uniform::Uniform(Uniform&& other)
    : Object{std::move(other)}, program_{other.program_}, location_{other.location_}
{
}

Uniform& Uniform::operator=(Uniform&& other)
{
    this->~Uniform();
    Object::operator=(std::move(other));
    program_ = other.program_;
    location_ = other.location_;
    return *this;
}

Uniform::Uniform(unsigned int program, int location)
    : Object{0}, program_{program}, location_{location}
{
}

} // namespace gl
