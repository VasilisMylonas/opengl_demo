#pragma once

#include "logger.hpp"
#include "timer.hpp"

#include <string>
#include <string_view>
#include <iostream>

class ApplicationBase
{
private:
    static void on_glfw_error(int error, const char *description);
    static void init_glfw();
    static inline const Logger glfw_log{std::clog, "GLFW"};
    static inline const Logger glew_log{std::clog, "GLEW"};
    static inline const Logger opengl_log{std::clog, "OpenGL"};
    static inline const Logger engine_log{std::clog, "Engine"};

    std::string name_;

protected:
    const Logger &logger() const;
    virtual void init() = 0;
    virtual void render(Timer &timer) = 0;

public:
    ApplicationBase(std::string_view name);
    void start();
};
