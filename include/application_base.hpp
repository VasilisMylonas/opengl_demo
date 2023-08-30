#pragma once

#include "logger.hpp"
#include "window.hpp"

#include <iostream>

class ApplicationBase
{
private:
    static const Logger log_msg;

    static void on_glfw_error(int error, const char *description)
    {
        (void)error;
        log_msg("GLFW", description);
    }

    void init_glfw()
    {
        if (!glfwInit())
        {
            log_msg("GLFW", "Initialization failure");
            exit(EXIT_FAILURE);
        }

        atexit(glfwTerminate);
        glfwSetErrorCallback(on_glfw_error);
    }

public:
    void start()
    {
        init_glfw();

        glfwWindowHint(GLFW_SAMPLES, 4);
        Window window(1000, 400, "Pong");

        log_msg("OpenGL", "Version: %s", glGetString(GL_VERSION));
        log_msg("OpenGL", "Renderer: %s", glGetString(GL_RENDERER));

        init();

        double t0 = glfwGetTime();
        double t1 = 0;
        double dt = 0;
        int frame_count = 0;

        while (!window.should_close())
        {
            dt = t1 - t0;

            if (dt > FPS_SAMPLE_INTERVAL)
            {
                log_msg("Engine", "%.2lffps", frame_count / dt);
                t0 = glfwGetTime();
                frame_count = 0;
            }

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            render();

            window.swap_buffers();
            glfwPollEvents();

            t1 = glfwGetTime();
            frame_count++;
        }
    }

    virtual void init() = 0;
    virtual void render() = 0;
};

const Logger ApplicationBase::log_msg{std::clog};
