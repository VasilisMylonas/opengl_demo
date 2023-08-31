#pragma once

#include "logger.hpp"

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

protected:
    virtual void init() = 0;
    virtual void render() = 0;

public:
    void start();
};
