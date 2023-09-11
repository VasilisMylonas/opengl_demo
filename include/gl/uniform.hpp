#pragma once

#include "gl/object.hpp"

#include <glm/glm.hpp>

namespace gl
{

class Uniform : public Object
{
public:
    friend class Program;

    Uniform(Uniform&& other);
    Uniform& operator=(Uniform&& other);

    Uniform(const Uniform&) = delete;
    Uniform& operator=(const Uniform&) = delete;

    void set(const glm::vec1& vec);
    void set(const glm::vec2& vec);
    void set(const glm::vec3& vec);
    void set(const glm::vec4& vec);

    void set(const glm::mat4& mat);

    void set(int value);
    void set(std::size_t count, const int* values);

    // TODO: more types

    // TODO: getters

    int location() const;

protected:
    Uniform(unsigned int program, int location);

private:
    unsigned int program_;
    int location_;
};

} // namespace gl
