#include "vcl/command_line.hpp"

#include <algorithm>

namespace vcl
{

std::string_view CommandLine::program_name() const
{
    return program_name_;
}

const std::vector<std::string_view>& CommandLine::args() const
{
    return args_;
}

CommandLine::CommandLine(int argc, const char** argv) : program_name_{argv[0]}
{
    // TODO: path separator
    auto index = program_name_.rfind('/');
    if (index != std::string_view::npos)
    {
        program_name_.remove_prefix(index + 1);
    }

    for (int i = 1; i < argc; i++)
    {
        args_.emplace_back(argv[i]);
    }
}

static bool is_key(std::string_view arg)
{
    return arg[0] == '-';
}

void CommandLine::getopt(Option& option)
{
    // TODO: handle --long-option=value and -abcd

    std::array<std::string_view, 2> keys = {
        option.long_key_,
        option.short_key_,
    };

    auto found = std::find_first_of(args_.begin(), args_.end(), keys.begin(), keys.end());

    if (found == args_.end()) // Key not found
    {
        // TODO: error
        return;
    }

    found = args_.erase(found);

    if (option.is_flag_)
    {
        option.set_value("true");
    }

    if (found == args().end() || is_key(*found)) // No argument
    {
        // TODO: error?
        return;
    }

    option.set_value(*found);
}

std::string CommandLine::Option::make_short_string() const
{
    std::string short_option{short_key_};

    if (short_key_.empty())
    {
        short_option += "   ";
    }
    else
    {
        short_option += ',';
    }

    return short_option;
}

std::string CommandLine::Option::make_long_string(std::size_t size) const
{
    std::string long_option{long_key_};

    if (!is_flag_)
    {
        long_option += "=<VALUE>";
    }

    long_option.resize(size, ' ');
    return long_option;
}

std::string CommandLine::Option::make_description_string(std::size_t size) const
{
    std::string descr{description_};
    descr.resize(size, ' ');
    return descr;
}

void CommandLine::Option::set_value(std::string_view value) const
{
    set_(value, argument_);
}

} // namespace vcl
