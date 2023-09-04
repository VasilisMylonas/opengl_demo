#pragma once

#include "gl/attribute.hpp"

#include <unordered_map>
#include <initializer_list>
#include <utility>

namespace gl
{
    class Layout
    {
    private:
        std::unordered_map<std::size_t, Attribute> attributes_{};
        std::size_t stride_{0};

    public:
        Layout() = default;

        Layout(std::initializer_list<std::pair<const std::size_t, Attribute>> list)
            : attributes_{list}
        {
        }

        std::size_t count() const
        {
            return attributes_.size();
        }

        const Attribute &operator[](std::size_t index) const
        {
            return attributes_.at(index);
        }

        Attribute &operator[](std::size_t index)
        {
            return attributes_[index];
        }
    };
} // namespace gl
