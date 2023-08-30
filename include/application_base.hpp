#pragma once

#include "logger.hpp"

#include <iostream>

class ApplicationBase
{
private:
    static void on_glfw_error(int error, const char *description);
    static void init_glfw();
    static inline const Logger<std::clog> glfw_log{"GLFW"};
    static inline const Logger<std::clog> glew_log{"GLEW"};
    static inline const Logger<std::clog> opengl_log{"OpenGL"};
    static inline const Logger<std::clog> engine_log{"Engine"};

public:
    void start();

    virtual void init() = 0;
    virtual void render() = 0;
};
