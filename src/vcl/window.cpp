#include "vcl/window.hpp"

#include "gl/renderer.hpp"

#include <GLFW/glfw3.h>

namespace vcl
{

// TODO
// static Window *get_wrapper(GLFWwindow *handle)
// {
//     return static_cast<Window *>(glfwGetWindowUserPointer(handle));
// }

static void on_resize_internal(GLFWwindow* window, int width, int height)
{
    (void)window;
    auto previous = glfwGetCurrentContext();

    glfwMakeContextCurrent(window);
    glViewport(0, 0, width, height);
    glfwMakeContextCurrent(previous);
}

Window::Window(int width, int height, const char* title)
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

    glfwSetFramebufferSizeCallback(handle_, on_resize_internal);
    on_resize_internal(handle_, width, height);

    make_current();
}

Window::Window(Window&& other)
{
    handle_ = other.handle_;
    glfwSetWindowUserPointer(handle_, this);
    other.handle_ = nullptr;
}

Window& Window::operator=(Window&& other)
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

Window& Window::resize(int width, int height)
{
    glfwSetWindowSize(handle_, width, height);
    return *this;
}

bool Window::should_close() const
{
    return glfwWindowShouldClose(handle_);
}

Window& Window::close()
{
    glfwSetWindowShouldClose(handle_, GLFW_TRUE);
    return *this;
}

Window& Window::swap_buffers()
{
    glfwSwapBuffers(handle_);
    return *this;
}

Window& Window::show()
{
    glfwShowWindow(handle_);
    return *this;
}

Window& Window::hide()
{
    glfwHideWindow(handle_);
    return *this;
}

Window& Window::attention()
{
    glfwRequestWindowAttention(handle_);
    return *this;
}

Window& Window::restore()
{
    glfwRestoreWindow(handle_);
    return *this;
}

Window& Window::minimize()
{
    glfwIconifyWindow(handle_);
    return *this;
}

Window& Window::maximize()
{
    glfwMaximizeWindow(handle_);
    return *this;
}

Window& Window::focus()
{
    glfwFocusWindow(handle_);
    return *this;
}

Window& Window::make_current()
{
    glfwMakeContextCurrent(handle_);

    glewExperimental = GL_TRUE;

    auto code = glewInit();
    if (code != GLEW_OK)
    {
        // TODO: throw
    }

    return *this;
}

bool Window::current() const
{
    return glfwGetCurrentContext() == handle_;
}

Window& Window::swap_interval(int interval)
{
    auto previous = glfwGetCurrentContext();
    make_current();
    glfwSwapInterval(interval);
    glfwMakeContextCurrent(previous);
    return *this;
}

} // namespace vcl
