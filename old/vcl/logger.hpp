#pragma once

#include <cstdarg>
#include <ostream>
#include <string_view>

namespace vcl
{

class Logger
{
public:
    enum class Level
    {
        trace,
        debug,
        info,
        warn,
        error,
    };

    Logger(std::ostream& stream, std::string_view source, Level level = Level::info);
    ~Logger();
    Logger(Logger&& other);
    Logger& operator=(Logger&& other);
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void set_level(Level level);
    Level level() const;

    void trace(const char* format, ...) const;
    void debug(const char* format, ...) const;
    void info(const char* format, ...) const;
    void warn(const char* format, ...) const;
    void error(const char* format, ...) const;

protected:
    static std::string_view level_to_str(Level level);

    virtual void log(Level level, const char* format, std::va_list args) const;

private:
    std::string_view source_;
    std::ostream* stream_;
    Level level_;
};

} // namespace vcl
