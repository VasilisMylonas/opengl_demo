#pragma once

#include "gl/object.hpp"

#include <typeindex>
#include <unordered_map>
#include <vector>

namespace gl
{
    class Layout
    {
    private:
        struct Attribute
        {
            GLenum type;
            GLboolean normalized;
            GLint count;
            std::size_t size;

            Attribute(
                GLenum type,
                GLboolean normalized,
                GLint count,
                std::size_t size)
                : type{type}, normalized{normalized}, count{count}, size{size}
            {
            }
        };

        std::vector<Attribute> attributes_{};
        std::size_t stride_{0};

        static inline std::unordered_map<std::type_index, GLenum> gl_type_ = {
            {typeid(unsigned char), GL_UNSIGNED_BYTE},
            {typeid(unsigned short), GL_UNSIGNED_SHORT},
            {typeid(unsigned int), GL_UNSIGNED_INT},
            {typeid(char), GL_BYTE},
            {typeid(short), GL_SHORT},
            {typeid(int), GL_INT},
            {typeid(float), GL_FLOAT},
            {typeid(double), GL_DOUBLE},
        };

    public:
        std::size_t count() const
        {
            return attributes_.size();
        }

        std::size_t stride() const
        {
            return stride_;
        }

        const Attribute &operator[](std::size_t index) const
        {
            return attributes_[index];
        }

        Attribute &operator[](std::size_t index)
        {
            return attributes_[index];
        }

        const std::vector<Attribute> &attributes() const
        {
            return attributes_;
        }

        template <std::size_t Count, class T>
        void push(bool normalized = false)
        {
            stride_ += Count * sizeof(T);
            attributes_.emplace_back(
                gl_type_.at(typeid(T)),
                static_cast<GLboolean>(normalized),
                static_cast<GLint>(Count),
                sizeof(T));
        }
    };
} // namespace gl
