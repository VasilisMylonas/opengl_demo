#pragma once

#include "object.hpp"

#include <vector>

namespace gl
{
    struct VertexAttribute
    {
        VertexAttribute(GLenum type, GLboolean normalized, GLint count, std::size_t size)
            : type{type}, normalized{normalized}, count{count}, size{size}
        {
        }

        GLenum type;
        GLboolean normalized;
        GLint count;
        std::size_t size;
    };

    class VertexLayout
    {
    private:
        std::vector<VertexAttribute> attributes_{};
        std::size_t stride_{0};

    public:
        std::size_t stride() const
        {
            return stride_;
        }

        const std::vector<VertexAttribute> &attributes() const
        {
            return attributes_;
        }

        template <class T>
        void push(std::size_t count, bool normalized = false) = delete;
    };

    template <>
    inline void VertexLayout::push<int>(std::size_t count, bool normalized)
    {
        attributes_.emplace_back(GL_INT, normalized, count, sizeof(int));
        stride_ += count * sizeof(int);
    }

    template <>
    inline void VertexLayout::push<float>(std::size_t count, bool normalized)
    {
        attributes_.emplace_back(GL_FLOAT, normalized, count, sizeof(float));
        stride_ += count * sizeof(float);
    }
} // namespace gl