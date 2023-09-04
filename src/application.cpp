#include "application.hpp"

#include "config.hpp"

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

const Logger &Application::logger() const
{
    return logger_;
}

Application::Application(int argc, const char *argv[])
    : logger_{std::clog, "Application"}, argc_{argc}, argv_{argv}
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

void Application::render()
{
}

void Application::logic()
{
}

void Application::input()
{
}

void Application::start()
{
    Window window = init();
    window.make_current();

    logger().info("OpenGL Version: %s", glGetString(GL_VERSION));
    logger().info("OpenGL Renderer: %s", glGetString(GL_RENDERER));

    while (!window.should_close())
    {
        glfwPollEvents();
        input();
        logic();
        render();
        window.swap_buffers();
    }
}