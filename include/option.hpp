#pragma once

#include <optional>
#include <string>
#include <string_view>

#include "util.hpp"

class Option
{
private:
    std::optional<char> short_key_;
    std::optional<std::string> value_;
    std::string long_key_;
    std::string description_;
    std::optional<std::string> default_value_;

public:
    Option(std::string_view long_key, std::string_view description, std::string_view default_value);
    Option(std::string_view long_key, std::string_view description);
    Option(char short_key,
           std::string_view long_key,
           std::string_view description,
           std::string_view default_value);
    Option(char short_key, std::string_view long_key, std::string_view description);

    const std::optional<char>& short_key() const;
    bool required() const;
    bool found() const;
    std::string_view value() const;
    std::string_view description() const;
    std::string_view long_key() const;

    void set_value(std::string_view value);

    std::string make_short_option() const;
    std::string make_long_option(std::size_t size) const;
    std::string make_description(std::size_t size) const;
    operator bool() const;

    // template <class T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    // T as() const
    // {
    //     T retval;
    //     std::from_chars(value_.data(), value_.data() + value_.size(), retval);
    //     return retval;
    // }
};