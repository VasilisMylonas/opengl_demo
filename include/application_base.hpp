#pragma once

#include "logger.hpp"
#include "window.hpp"

#include <string>
#include <string_view>

class ApplicationBase
{
private:
    std::string name_;
    Logger logger_;

    static void on_glfw_error(int error, const char *description);

protected:
    virtual Window init() = 0;
    virtual void render() = 0;

public:
    ApplicationBase(std::string_view name);
    virtual ~ApplicationBase();
    void start(int argc, const char *argv[]);
    const std::string &name() const;
    const Logger &logger() const;
};
