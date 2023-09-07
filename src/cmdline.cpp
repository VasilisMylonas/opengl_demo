#include "cmdline.hpp"

bool CmdLine::is_empty(std::string_view arg)
{
    return arg.empty() || arg == "-" || arg == "--";
}

bool CmdLine::is_long(std::string_view option)
{
    auto index = option.find('=', 0);
    return index == std::string_view::npos || index == 0;
}

CmdLine::ArgType CmdLine::classify_arg(std::string_view& arg)
{
    if (is_empty(arg))
    {
        return ArgType::EMPTY;
    }

    if (arg[0] != '-')
    {
        return ArgType::VALUE;
    }
    arg.remove_prefix(1);

    if (arg[0] != '-')
    {
        return arg.size() == 1 ? ArgType::SHORT : ArgType::SHORT_MULTI;
    }
    arg.remove_prefix(1);

    return is_long(arg) ? ArgType::LONG : ArgType::LONG_ASSIGN;
}

void CmdLine::handle_short_multi(std::string_view arg)
{
    for (size_t i = 0; i < arg.size(); i++)
    {
        options_[arg.substr(i, 1)] = "true";
    }
    current_key_ = "";
}

void CmdLine::handle_value(std::string_view arg)
{
    if (!current_key_.empty())
    {
        options_[current_key_] = arg;
    }
    else
    {
        values_.push_back(arg);
    }
    current_key_ = "";
}

void CmdLine::handle_long_assign(std::string_view arg)
{
    auto index = arg.find('=', 0);
    options_[arg.substr(0, index)] = arg.substr(index + 1);
    current_key_ = "";
}

void CmdLine::parse(int argc, const char** argv)
{
    current_key_ = "";

    for (int i = 0; i < argc; i++)
    {
        std::string_view arg = argv[i];
        switch (classify_arg(arg))
        {
        case ArgType::SHORT:
        case ArgType::LONG:
            options_[arg] = "true";
            current_key_ = arg;
            break;
        case ArgType::VALUE:
            handle_value(arg);
            break;
        case ArgType::SHORT_MULTI:
            handle_short_multi(arg);
            break;
        case ArgType::LONG_ASSIGN:
            handle_long_assign(arg);
            break;
        default:
            current_key_ = "";
            break;
        }
    }
}

std::string_view CmdLine::program_name() const
{
    return program_name_;
}

const std::vector<std::string_view>& CmdLine::values() const
{
    return values_;
}

const std::unordered_map<std::string_view, std::string_view>& CmdLine::options() const
{
    return options_;
}

CmdLine::CmdLine(int argc, const char** argv) : program_name_{argv[0]}
{
    // TODO: path separator
    auto index = program_name_.rfind('/');
    if (index != std::string_view::npos)
    {
        program_name_.remove_prefix(index + 1);
    }
    parse(argc, argv);
}

void CmdLine::set_if_key_exists(Option& option, std::string_view key) const
{
    if (options_.find(key) != options_.end())
    {
        option.set_value(options_.at(key));
    }
}