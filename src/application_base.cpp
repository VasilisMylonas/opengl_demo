#include "application_base.hpp"

#include "config.hpp"
#include "window.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void ApplicationBase::on_glfw_error(int error, const char *description)
{
    (void)error;
    glfw_log.error(description);
}

void ApplicationBase::init_glfw()
{
    if (!glfwInit())
    {
        glew_log.error("Initialization failure");
        exit(EXIT_FAILURE);
    }

    atexit(glfwTerminate);
    glfwSetErrorCallback(on_glfw_error);
}

void ApplicationBase::start()
{
    init_glfw();

    glfwWindowHint(GLFW_SAMPLES, 4);
    Window window(1000, 400, "Pong");

    opengl_log.info("Version: %s", glGetString(GL_VERSION));
    opengl_log.info("Renderer: %s", glGetString(GL_RENDERER));

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
            engine_log.info("%.2lffps", frame_count / dt);
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