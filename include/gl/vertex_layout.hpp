#pragma once

#include "gl/errors.hpp"

#include <glm/glm.hpp>
#include <vector>

namespace gl
{

struct vertex_attribute
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
    gl::vertex_attribute                                                                           \
    {                                                                                              \
        sizeof(type), offsetof(type, member), gl::type_of<decltype(type::member)>(),               \
    }

using vertex_layout = std::vector<vertex_attribute>;

} // namespace gl
