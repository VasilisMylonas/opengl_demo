#include "option.hpp"

char Option::short_key() const
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

std::string Option::make_short_string() const
{
    std::string short_option;

    if (short_key_)
    {
        short_option += '-';
        short_option += short_key_;
        short_option += ',';
    }
    else
    {
        short_option += "   ";
    }

    return short_option;
}

std::string Option::make_long_string(std::size_t size) const
{
    std::string long_option{"--"};

    long_option += long_key_;
    long_option.resize(size, ' ');
    return long_option;
}

std::string Option::make_description_string(std::size_t size) const
{
    std::string descr = description_;
    descr.resize(size, ' ');
    return descr;
}

Option::Option(char short_key,
               std::string_view long_key,
               std::string_view description,
               void* argument,
               Setter* setter)
    : short_key_{short_key},
      long_key_{long_key},
      description_{description},
      argument_{argument},
      set_{setter}
{
}

void Option::set_value(std::string_view value) const
{
    set_(value, argument_);
}