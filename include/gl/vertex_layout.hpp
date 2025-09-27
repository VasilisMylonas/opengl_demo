#pragma once

#include "gl/errors.hpp"

#include <glm/glm.hpp>
#include <vector>

namespace gl
{

struct VertexAttribute
{
    unsigned stride;
    unsigned offset;
    std::pair<unsigned, int> type;
};

template <typename T>
std::pair<unsigned, int> type_of() = delete;

template <>
inline std::pair<unsigned, int> type_of<float>()
{
    return {1, GL_FLOAT};
}

template <>
inline std::pair<unsigned, int> type_of<double>()
{
    return {1, GL_DOUBLE};
}

template <>
inline std::pair<unsigned, int> type_of<int>()
{
    return {1, GL_INT};
}

template <>
inline std::pair<unsigned, int> type_of<unsigned int>()
{
    return {1, GL_UNSIGNED_INT};
}

template <>
inline std::pair<unsigned, int> type_of<glm::vec1>()
{
    return {1, GL_FLOAT};
}

template <>
inline std::pair<unsigned, int> type_of<glm::vec2>()
{
    return {2, GL_FLOAT};
}

template <>
inline std::pair<unsigned, int> type_of<glm::vec3>()
{
    return {3, GL_FLOAT};
}

template <>
inline std::pair<unsigned, int> type_of<glm::vec4>()
{
    return {4, GL_FLOAT};
}

#define VERTEX_ATTRIBUTE(type, member)                                                             \
    gl::VertexAttribute                                                                            \
    {                                                                                              \
        sizeof(type), offsetof(type, member), gl::type_of<decltype(type::member)>(),               \
    }

using VertexLayout = std::vector<VertexAttribute>;

} // namespace gl
