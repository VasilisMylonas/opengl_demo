#pragma once

#include <optional>
#include <string>
#include <string_view>

class Option
{
private:
    std::optional<char> short_key_;
    std::string long_key_;
    std::string description_;
    std::optional<std::string> value_;
    bool has_arg_;

public:
    Option(std::string_view long_key, std::string_view description, bool has_arg);
    Option(char short_key, std::string_view long_key, std::string_view description, bool has_arg);

    const std::optional<char>& short_key() const;
    std::string_view description() const;
    std::string_view long_key() const;

    const std::optional<std::string>& value() const;
    void set_value(std::string_view value);

    std::string make_short_string() const;
    std::string make_long_string(std::size_t size) const;
    std::string make_description_string(std::size_t size) const;
};