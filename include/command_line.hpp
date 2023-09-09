#pragma once

#include "convert.hpp"

#include <array>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <vector>

class CommandLine
{
public:
    class Option
    {
    public:
        friend class CommandLine;

        using Setter = void(std::string_view, void*);

        Option(const std::string& short_key,
               const std::string& long_key,
               const std::string& description,
               void* argument,
               Setter* setter,
               bool is_flag)
            : short_key_{short_key},
              long_key_{long_key},
              description_{description},
              argument_{argument},
              set_{setter},
              is_flag_{is_flag}
        {
        }

    private:
        void set_value(std::string_view value) const;
        std::string make_short_string() const;
        std::string make_long_string(std::size_t size) const;
        std::string make_description_string(std::size_t size) const;

        std::string short_key_;
        std::string long_key_;
        std::string description_;
        void* argument_;
        Setter* set_;
        bool is_flag_;
    };

    CommandLine(int argc, const char** argv);

    std::string_view program_name() const;
    const std::vector<std::string_view>& args() const;
    void getopt(Option& option);

    template <std::size_t N>
    void usage(const std::array<Option, N>& options, std::string_view program_description) const
    {
        std::cout << "Usage: " << program_name() << " [OPTION...]\n\n";
        std::cout << program_description << "\n\nOptions:\n";

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
    std::vector<std::string_view> args_;
    std::string_view program_name_;
};

template <typename T>
CommandLine::Option
make_option(std::string_view long_key, std::string_view description, std::optional<T>& arg)
{
    return CommandLine::Option{
        "",
        std::string{"--"} += long_key,
        std::string{description},
        reinterpret_cast<void*>(&arg),
        [](std::string_view value, void* arg)
        { *reinterpret_cast<std::optional<T>*>(arg) = Convert::to<T>(value); },
        std::is_same_v<T, bool>,
    };
}

template <typename T>
CommandLine::Option make_option(char short_key,
                                std::string_view long_key,
                                std::string_view description,
                                std::optional<T>& arg)
{
    return CommandLine::Option{
        std::string{"-"} += short_key,
        std::string{"--"} += long_key,
        std::string{description},
        reinterpret_cast<void*>(&arg),
        [](std::string_view value, void* arg)
        { *reinterpret_cast<std::optional<T>*>(arg) = Convert::to<T>(value); },
        std::is_same_v<T, bool>,
    };
}
