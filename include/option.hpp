#pragma once

#include "convert.hpp"

#include <string>
#include <string_view>

class Option
{
public:
    using Setter = void(std::string_view, void*);

    Option(char short_key,
           std::string_view long_key,
           std::string_view description,
           void* argument,
           Setter* setter);

    char short_key() const;
    std::string_view description() const;
    std::string_view long_key() const;
    void set_value(std::string_view value) const;

    std::string make_short_string() const;
    std::string make_long_string(std::size_t size) const;
    std::string make_description_string(std::size_t size) const;

private:
    char short_key_;
    std::string long_key_;
    std::string description_;
    void* argument_;
    Setter* set_;
};

template <typename T>
void setter(std::string_view value, void* arg)
{
    *reinterpret_cast<T*>(arg) = Convert::to<T>(value);
}

template <typename T>
Option make_option(char short_key, std::string_view long_key, std::string_view description, T& arg)
{
    return {
        short_key,
        long_key,
        description,
        reinterpret_cast<void*>(&arg),
        setter<T>,
    };
}
