#include "option.hpp"

Option::operator bool() const
{
    return Convert::to_bool(value());
}

std::string_view Option::value() const
{
    if (found())
    {
        return value_.value();
    }

    if (!required())
    {
        return default_value_.value();
    }

    // TODO: error
    return "";
}

const std::optional<char>& Option::short_key() const
{
    return short_key_;
}

std::string_view Option::long_key() const
{
    return long_key_;
}

std::string_view Option::description() const
{
    return description_;
}

bool Option::required() const
{
    return !default_value_.has_value();
}

bool Option::found() const
{
    return value_.has_value();
}

void Option::set_value(std::string_view value)
{
    value_ = value;
}

std::string Option::make_short_option() const
{
    std::string short_option;

    if (short_key_)
    {
        short_option += '-';
        short_option += short_key_.value();
        short_option += ',';
    }
    else
    {
        short_option += "   ";
    }

    return short_option;
}

std::string Option::make_long_option(std::size_t size) const
{
    std::string long_option{"--"};

    long_option += long_key_;

    if (required())
    {
        long_option += "=<VALUE>";
    }

    long_option.resize(size, ' ');
    return long_option;
}

std::string Option::make_description(std::size_t size) const
{
    std::string descr = description_;
    descr.resize(size, ' ');
    return descr;
}

Option::Option(std::string_view long_key,
               std::string_view description,
               std::string_view default_value)
    : long_key_{long_key}, description_{description}, default_value_{default_value}
{
}

Option::Option(std::string_view long_key, std::string_view description)
    : long_key_{long_key}, description_{description}
{
}

Option::Option(char short_key,
               std::string_view long_key,
               std::string_view description,
               std::string_view default_value)
    : short_key_{short_key},
      long_key_{long_key},
      description_{description},
      default_value_{default_value}
{
}

Option::Option(char short_key, std::string_view long_key, std::string_view description)
    : short_key_{short_key}, long_key_{long_key}, description_{description}
{
}
