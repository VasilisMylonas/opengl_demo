#include "gl/uniform.hpp"

namespace gl
{

void Uniform::set(float v0)
{
    GL_CALL(glProgramUniform1f(program_, static_cast<int>(handle_), v0));
}

void Uniform::set(float v0, float v1)
{
    GL_CALL(glProgramUniform2f(program_, static_cast<int>(handle_), v0, v1));
}

void Uniform::set(float v0, float v1, float v2)
{
    GL_CALL(glProgramUniform3f(program_, static_cast<int>(handle_), v0, v1, v2));
}

void Uniform::set(float v0, float v1, float v2, float v3)
{
    GL_CALL(glProgramUniform4f(program_, static_cast<int>(handle_), v0, v1, v2, v3));
}

void Uniform::set(const glm::vec1& vec)
{
    Uniform::set(vec.x);
}

void Uniform::set(const glm::vec2& vec)
{
    Uniform::set(vec.x, vec.y);
}

void Uniform::set(const glm::vec3& vec)
{
    Uniform::set(vec.x, vec.y, vec.z);
}

void Uniform::set(const glm::vec4& vec)
{
    Uniform::set(vec.x, vec.y, vec.z, vec.w);
}

} // namespace gl
