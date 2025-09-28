#pragma once

#include "gl/vertex_layout.hpp"

#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 position{0, 0, 0};
    glm::vec3 normal{0, 0, 1};
    glm::vec4 color{1, 1, 1, 0};
    glm::vec2 uv{0, 0};
    unsigned int texture{0};

    static inline gl::vertex_layout layout()
    {
        gl::vertex_layout layout;
        layout.push_back(VERTEX_ATTRIBUTE(Vertex, position));
        layout.push_back(VERTEX_ATTRIBUTE(Vertex, normal));
        layout.push_back(VERTEX_ATTRIBUTE(Vertex, color));
        layout.push_back(VERTEX_ATTRIBUTE(Vertex, uv));
        layout.push_back(VERTEX_ATTRIBUTE(Vertex, texture));
        return layout;
    }
};
