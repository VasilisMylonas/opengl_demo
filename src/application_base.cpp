#include "application_base.hpp"

#include "config.hpp"
#include "window.hpp"
#include "timer.hpp"
#include "renderer.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

const std::string &ApplicationBase::name() const
{
    return name_;
}

const Logger &ApplicationBase::logger() const
{
    return logger_;
}

ApplicationBase::ApplicationBase(std::string_view name)
    : name_{name}, logger_{std::clog, name}
{
    if (!glfwInit())
    {
        // TODO: throw
    }

    glfwSetErrorCallback(on_glfw_error);
}

ApplicationBase::~ApplicationBase()
{
    glfwTerminate();
}

void ApplicationBase::on_glfw_error(int error, const char *description)
{
    (void)error;
    (void)description;
    // TODO
    // logger_.error(description);
}

void ApplicationBase::start(int argc, const char *argv[])
{
    (void)argc;
    (void)argv;

    glfwWindowHint(GLFW_SAMPLES, 4);
    Window window = init();

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