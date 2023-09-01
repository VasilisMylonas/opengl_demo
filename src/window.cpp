#include "window.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// static Window *get_wrapper(GLFWwindow *handle)
// {
//     return static_cast<Window *>(glfwGetWindowUserPointer(handle));
// }

static void on_resize_internal(GLFWwindow *window, int width, int height)
{
    (void)window;
    auto previous = glfwGetCurrentContext();

    glfwMakeContextCurrent(window);
    glViewport(0, 0, width, height);
    glfwMakeContextCurrent(previous);
}

Window::Window(int width, int height, const char *title)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // TODO: anti-aliasing
    glfwWindowHint(GLFW_SAMPLES, 16);

    handle_ = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!handle_)
    {
        // TODO: throw
    }

    glfwMakeContextCurrent(handle_);
    glewExperimental = GL_TRUE;

    auto code = glewInit();
    if (code != GLEW_OK)
    {
        // TODO: throw
    }

    glfwSetFramebufferSizeCallback(handle_, on_resize_internal);
    on_resize_internal(handle_, width, height);
}

Window::Window(Window &&other)
{
    handle_ = other.handle_;
    glfwSetWindowUserPointer(handle_, this);
    other.handle_ = nullptr;
}

Window &Window::operator=(Window &&other)
{
    handle_ = other.handle_;
    glfwSetWindowUserPointer(handle_, this);
    other.handle_ = nullptr;
    return *this;
}

Window::~Window()
{
    if (handle_)
    {
        glfwDestroyWindow(handle_);
    }
}

std::pair<int, int> Window::size() const
{
    int width, height;
    glfwGetWindowSize(handle_, &width, &height);
    return {width, height};
}

void Window::resize(int width, int height)
{
    glfwSetWindowSize(handle_, width, height);
}

bool Window::should_close() const
{
    return glfwWindowShouldClose(handle_);
}

void Window::close()
{
    glfwSetWindowShouldClose(handle_, GLFW_TRUE);
}

void Window::swap_buffers()
{
    glfwSwapBuffers(handle_);
}

void Window::make_current()
{
    glfwMakeContextCurrent(handle_);
}

bool Window::current() const
{
    return glfwGetCurrentContext() == handle_;
}

void Window::swap_interval(int interval)
{
    auto previous = glfwGetCurrentContext();
    make_current();
    glfwSwapInterval(interval);
    glfwMakeContextCurrent(previous);
}
