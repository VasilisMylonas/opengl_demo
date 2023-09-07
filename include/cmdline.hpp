#pragma once

#include <array>
#include <charconv>
#include <iomanip>
#include <iostream>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#include "option.hpp"

class CmdLine
{
public:
    CmdLine(int argc, const char** argv);

    std::string_view program_name() const;
    const std::vector<std::string_view>& values() const;
    const std::unordered_map<std::string_view, std::string_view>& options() const;

    bool getopt(Option& option) const;

    template <std::size_t N>
    void usage(const std::array<Option, N>& options, std::string_view program_description) const
    {
        std::cout << "Usage: " << program_name() << " [OPTION...]\n";
        std::cout << program_description << "\n\n";

        for (const Option& option : options)
        {
            std::string short_option = option.make_short_string();
            std::string long_option = option.make_long_string(32);
            std::string description = option.make_description_string(64);

            std::cout << short_option << ' ' << long_option << ' ' << description << '\n';
        }

        std::cout << std::endl;
    }

private:
    std::unordered_map<std::string_view, std::string_view> options_;
    std::vector<std::string_view> values_;
    std::string_view program_name_;
    std::string_view current_key_;

    enum class ArgType
    {
        SHORT,       // -x xxx
        SHORT_MULTI, // -abcd
        LONG,        // --xx-xx xxx
        LONG_ASSIGN, // --xx-xx=xxx
        EMPTY,       // - --
        VALUE,       // any other
    };

    bool set_if_key_exists(Option& option, std::string_view key) const;

    void parse(int argc, const char** argv);
    void handle_long_assign(std::string_view arg);
    void handle_value(std::string_view arg);
    void handle_short_multi(std::string_view arg);

    static bool is_empty(std::string_view arg);
    static bool is_long(std::string_view arg);
    static ArgType classify_arg(std::string_view& arg);
};
