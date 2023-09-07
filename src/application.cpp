#include "application.hpp"

#include "config.hpp"

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

const Logger& Application::logger() const
{
    return logger_;
}

Application::Application(int argc, const char* argv[])
    : logger_{std::clog, "Application"}, argc_{argc}, argv_{argv}
{
    if (!glfwInit())
    {
        // TODO: throw
    }

    glfwSetErrorCallback(on_glfw_error);

    if (current_)
    {
        // TODO: error there can only be one application running
    }

    current_ = this;
}

Application::Application(Application&& other)
    : logger_{std::move(other.logger_)}, argc_{other.argc_}, argv_{other.argv_}
{
    current_ = this;
}

Application::~Application()
{
    glfwTerminate();
    current_ = nullptr;
}

void Application::on_glfw_error(int error, const char* description)
{
    (void)error;
    current().logger().error(description);
}

void Application::poll_events() const
{
    glfwPollEvents();
}

Application& Application::current()
{
    if (!current_)
    {
        // TODO: error
    }

    return *current_;
}

void Application::main_loop(Window& window)
{
    logger().info("OpenGL Version: %s", glGetString(GL_VERSION));
    logger().info("OpenGL Renderer: %s", glGetString(GL_RENDERER));

    while (!window.should_close())
    {
        poll_events();
        window.render();
        window.swap_buffers();
    }
}

Application* Application::current_;