#pragma once

#include "logger.hpp"
#include "window.hpp"

#include <string>
#include <string_view>

class Application
{
private:
    std::string name_;
    Logger logger_;

    static void on_glfw_error(int error, const char *description);

protected:
    virtual Window init() = 0;
    virtual void render() = 0;

public:
    Application(std::string_view name);
    virtual ~Application();
    void start(int argc, const char *argv[]);
    const std::string &name() const;
    const Logger &logger() const;
};
