#pragma once

#include "gl/object.hpp"
#include "glm/glm.hpp"

namespace gl
{

class Uniform : public Object
{
public:
    friend class Shader;

    void set(float v0);
    void set(float v0, float v1);
    void set(float v0, float v1, float v2);
    void set(float v0, float v1, float v2, float v3);
    void set(const glm::vec1& vec);
    void set(const glm::vec2& vec);
    void set(const glm::vec3& vec);
    void set(const glm::vec4& vec);

private:
    unsigned int program_;

    Uniform(unsigned int program, unsigned int handle)
    {
        program_ = program;
        handle_ = handle;
    }
};

} // namespace gl
