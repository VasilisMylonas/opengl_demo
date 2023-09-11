#include "vcl/window.hpp"

#include "gl/renderer.hpp"

#include <GLFW/glfw3.h>

#include <functional>

namespace vcl
{

static void with_context(GLFWwindow* window, std::function<void()> function)
{
    GLFWwindow* previous = glfwGetCurrentContext();
    glfwMakeContextCurrent(window);
    function();
    glfwMakeContextCurrent(previous);
}

static Window* get_wrapper(GLFWwindow* handle)
{
    return static_cast<Window*>(glfwGetWindowUserPointer(handle));
}

std::pair<int, int> Window::scroll() const
{
    auto value = scroll_delta_;
    scroll_delta_ = {0, 0};
    return value;
}

void Window::on_mouse_scroll_internal(GLFWwindow* window, double x_offset, double y_offset)
{
    auto self = get_wrapper(window);
    self->scroll_delta_ = {x_offset, y_offset};
}

void Window::on_resize_internal(GLFWwindow* window, int width, int height)
{
    with_context(window, [width, height]() { glViewport(0, 0, width, height); });
}

Window::Window(int width, int height, const char* title) : scroll_delta_{0, 0}
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // TODO: anti-aliasing
    glfwWindowHint(GLFW_SAMPLES, 16);

    handle_ = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!handle_)
    {
        const char* msg;
        glfwGetError(&msg);
        throw CreationException{msg};
    }

    glfwSetWindowUserPointer(handle_, this);

    glfwSetFramebufferSizeCallback(handle_, on_resize_internal);
    glfwSetScrollCallback(handle_, on_mouse_scroll_internal);

    on_resize_internal(handle_, width, height);

    make_current();
}

Window::Window(Window&& other)
{
    handle_ = other.handle_;
    scroll_delta_ = other.scroll_delta_;
    glfwSetWindowUserPointer(handle_, this);
    other.handle_ = nullptr;
}

Window& Window::operator=(Window&& other)
{
    this->~Window();
    handle_ = other.handle_;
    scroll_delta_ = other.scroll_delta_;
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

GLFWwindow* Window::handle() const
{
    return handle_;
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
    glfwSetWindowShouldClose(handle_, true);
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

    // TODO: is this needed every time?
    glewExperimental = GL_TRUE;

    auto code = glewInit();
    if (code != GLEW_OK)
    {
        auto msg = reinterpret_cast<const char*>(glewGetErrorString(code));
        throw ContextException{msg};
    }

    return *this;
}

bool Window::current() const
{
    return glfwGetCurrentContext() == handle_;
}

Window& Window::swap_interval(int interval)
{
    with_context(handle_, [interval]() { glfwSwapInterval(interval); });
    return *this;
}

} // namespace vcl
