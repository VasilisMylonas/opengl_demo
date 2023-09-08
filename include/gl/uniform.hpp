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

    // TODO: more types

    // TODO: getters

private:
    unsigned int program_;

    Uniform(unsigned int program, unsigned int handle)
    {
        program_ = program;
        handle_ = handle;
    }
};

} // namespace gl
