#include "vcl/application.hpp"

#include "gl/renderer.hpp"

#include <GLFW/glfw3.h>
#include <iostream>

namespace vcl
{

const Logger& Application::logger() const
{
    return logger_;
}

const CommandLine& Application::command_line() const
{
    return command_line_;
}

CommandLine& Application::command_line()
{
    return command_line_;
}

Application::Application(int argc, const char* argv[])
    : logger_{std::clog, "Application"}, command_line_{argc, argv}
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
    : logger_{std::move(other.logger_)}, command_line_{other.command_line_}
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
    logger().info("OpenGL Version: %s", gl::Renderer::version());
    logger().info("OpenGL Renderer: %s", gl::Renderer::name());

    while (!window.should_close())
    {
        poll_events();
        window.render();
        window.swap_buffers();
    }
}

Application* Application::current_;

} // namespace vcl