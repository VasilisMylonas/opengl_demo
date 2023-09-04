#pragma once

#include "logger.hpp"
#include "window.hpp"

#include <string>
#include <string_view>

class Application
{
private:
    Logger logger_;
    int argc_;
    const char **argv_;
    static void on_glfw_error(int error, const char *description);

protected:
    virtual Window init() = 0;
    virtual void render();
    virtual void logic();
    virtual void input();

public:
    Application(int argc, const char *argv[]);
    virtual ~Application();
    void start();
    const Logger &logger() const;
};
