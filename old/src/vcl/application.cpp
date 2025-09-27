#include "vcl/application.hpp"

#include "gl/renderer.hpp"

#include <GLFW/glfw3.h>
#include <iostream>

namespace vcl
{

void Application::init()
{
    if (!glfwInit())
    {
        const char* msg;
        glfwGetError(&msg);
        throw CreationException(msg);
    }

    glfwSetErrorCallback(on_glfw_error);
}

void Application::fini()
{
    glfwTerminate();
}

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
        throw ContextException{"No currently running application instance."};
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