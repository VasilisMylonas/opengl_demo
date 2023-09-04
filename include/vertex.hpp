#pragma once

#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 position{0, 0, 0};
    glm::vec3 normal{0, 0, 1};
    glm::vec4 color{1, 1, 1, 0};
};
