#include "application.hpp"

#include "config.hpp"

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

const std::string &Application::name() const
{
    return name_;
}

const Logger &Application::logger() const
{
    return logger_;
}

Application::Application(std::string_view name)
    : name_{name}, logger_{std::clog, name}
{
    if (!glfwInit())
    {
        // TODO: throw
    }

    glfwSetErrorCallback(on_glfw_error);
}

Application::~Application()
{
    glfwTerminate();
}

void Application::on_glfw_error(int error, const char *description)
{
    (void)error;
    (void)description;
    // TODO
    // logger_.error(description);
}

void Application::start(int argc, const char *argv[])
{
    (void)argc;
    (void)argv;

    glfwWindowHint(GLFW_SAMPLES, 4);
    Window window = init();
    window.make_current();

    logger().info("OpenGL Version: %s", glGetString(GL_VERSION));
    logger().info("OpenGL Renderer: %s", glGetString(GL_RENDERER));

    while (!window.should_close())
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        render();
        window.swap_buffers();
        glfwPollEvents();
    }
}