#pragma once

#include "gl/object.hpp"

#include <typeindex>
#include <unordered_map>

namespace gl
{
    struct Attribute;

    template <std::size_t Count, class T>
    Attribute make_attribute(bool normalized = false);

    static inline const std::unordered_map<std::type_index, GLenum> type_mappings = {
        {typeid(unsigned char), GL_UNSIGNED_BYTE},
        {typeid(unsigned short), GL_UNSIGNED_SHORT},
        {typeid(unsigned int), GL_UNSIGNED_INT},
        {typeid(char), GL_BYTE},
        {typeid(short), GL_SHORT},
        {typeid(int), GL_INT},
        {typeid(float), GL_FLOAT},
    };

    class Attribute
    {
    public:
        Attribute() = default;

        friend class VertexArray;

        template <std::size_t Count, class T>
        friend Attribute make_attribute(bool normalized)
        {
            static_assert(Count > 0 && Count < 5, "Count must be 1, 2, 3 or 4");
            return {
                type_mappings.at(typeid(T)),
                static_cast<GLboolean>(normalized),
                static_cast<GLint>(Count),
                sizeof(T) * Count,
            };
        }

    private:
        GLenum type{GL_INT};
        GLboolean normalized{false};
        GLint count{0};
        GLsizei stride{0};

        Attribute(
            GLenum type,
            GLboolean normalized,
            GLint count,
            GLsizei stride)
            : type{type}, normalized{normalized}, count{count}, stride{stride}
        {
        }
    };

    template <class T>
    Attribute scalar()
    {
        return make_attribute<1, T>();
    }

    template <class T>
    Attribute vec2()
    {
        return make_attribute<2, T>();
    }

    template <class T>
    Attribute vec3()
    {
        return make_attribute<3, T>();
    }

    template <class T>
    Attribute vec4()
    {
        return make_attribute<4, T>();
    }
} // namespace gl
