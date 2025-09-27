#pragma once

#include "gl/errors.hpp"
#include <glm/glm.hpp>

namespace gl
{

class Uniform
{
public:
    friend class Program;

    Uniform(const Uniform&) = delete;
    Uniform& operator=(const Uniform&) = delete;

    Uniform(Uniform&& other) noexcept : program_{other.program_}, location_{other.location_}
    {
        other.program_ = 0;
        other.location_ = -1;
    }

    Uniform& operator=(Uniform&& other) noexcept
    {
        if (this != &other)
        {
            program_ = other.program_;
            location_ = other.location_;
            other.program_ = 0;
            other.location_ = -1;
        }
        return *this;
    }

    void set(const glm::vec1& vec)
    {
        GL_CALL(glProgramUniform1f(program_, location_, vec.x));
    }

    void set(const glm::vec2& vec)
    {
        GL_CALL(glProgramUniform2f(program_, location_, vec.x, vec.y));
    }

    void set(const glm::vec3& vec)
    {
        GL_CALL(glProgramUniform3f(program_, location_, vec.x, vec.y, vec.z));
    }

    void set(const glm::vec4& vec)
    {
        GL_CALL(glProgramUniform4f(program_, location_, vec.x, vec.y, vec.z, vec.w));
    }

    void set(const glm::mat4& mat)
    {
        GL_CALL(glProgramUniformMatrix4fv(program_, location_, 1, false, &mat[0][0]));
    }

    void set(int value)
    {
        GL_CALL(glProgramUniform1i(program_, location_, value));
    }

    void set(std::size_t count, const int* values)
    {
        GL_CALL(glProgramUniform1iv(program_, location_, static_cast<GLsizei>(count), values));
    }

    int location() const
    {
        return location_;
    }

protected:
    Uniform(unsigned int program, int location) : program_{program}, location_{location}
    {
    }

private:
    unsigned int program_;
    int location_;
};

} // namespace gl
