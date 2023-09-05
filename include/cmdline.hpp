#pragma once

#include <string_view>
#include <vector>
#include <unordered_map>
#include <utility>

class CmdLine
{
public:
    std::string_view program_name() const
    {
        return values_[0];
    }

    const std::vector<std::string_view> &values() const
    {
        return values_;
    }

    const std::unordered_map<std::string_view, std::string_view> &options() const
    {
        return options_;
    }

    CmdLine(int argc, const char **argv)
    {
        parse(argc, argv);
    }

private:
    std::unordered_map<std::string_view, std::string_view> options_;
    std::vector<std::string_view> values_;
    std::string_view current_key;

    enum class ArgType
    {
        SHORT,       // -x xxx
        SHORT_MULTI, // -abcd
        LONG,        // --xx-xx xxx
        LONG_ASSIGN, // --xx-xx=xxx
        EMPTY,       // - --
        VALUE,       // any other
    };

    bool is_empty_option(std::string_view option) const
    {
        return option.empty() || option == "-" || option == "--";
    }

    bool is_long_option(std::string_view option) const
    {
        auto index = option.find('=', 0);
        return index == std::string_view::npos || index == 0;
    }

    ArgType classify_arg(std::string_view &arg) const
    {
        if (is_empty_option(arg))
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

        return is_long_option(arg) ? ArgType::LONG : ArgType::LONG_ASSIGN;
    }

    void handle_short_multi(std::string_view arg)
    {
        for (size_t i = 0; i < arg.size(); i++)
        {
            options_[arg.substr(i, 1)] = "true";
        }
        current_key = "";
    }

    void handle_value(std::string_view arg)
    {
        if (!current_key.empty())
        {
            options_[current_key] = arg;
        }
        else
        {
            values_.push_back(arg);
        }
        current_key = "";
    }

    void handle_long_assign(std::string_view arg)
    {
        auto index = arg.find('=', 0);
        options_[arg.substr(0, index)] = arg.substr(index + 1);
        current_key = "";
    }

    void parse(int argc, const char **argv)
    {
        current_key = "";

        for (int i = 0; i < argc; i++)
        {
            std::string_view arg = argv[i];
            switch (classify_arg(arg))
            {
            case ArgType::SHORT:
            case ArgType::LONG:
                options_[arg] = "true";
                current_key = arg;
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
                current_key = "";
                break;
            };
        }
    }
};