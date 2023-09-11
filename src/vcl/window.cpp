#include "vcl/window.hpp"

#include "gl/renderer.hpp"

#include <GLFW/glfw3.h>

namespace vcl
{

static Window* get_wrapper(GLFWwindow* handle)
{
    return static_cast<Window*>(glfwGetWindowUserPointer(handle));
}

void Window::on_mouse_scroll_internal(GLFWwindow* window, double x_offset, double y_offset)
{
    auto self = get_wrapper(window);

    self->scroll_dx_ = x_offset;
    self->scroll_dy_ = y_offset;
}

std::pair<double, double> Window::scroll() const
{
    return {scroll_dx_, scroll_dy_};
}

void Window::on_resize_internal(GLFWwindow* window, int width, int height)
{
    auto previous = glfwGetCurrentContext();

    glfwMakeContextCurrent(window);
    glViewport(0, 0, width, height);
    glfwMakeContextCurrent(previous);
}

Window::Window(int width, int height, const char* title) : scroll_dx_{0}, scroll_dy_{0}
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

    glfwSetFramebufferSizeCallback(handle_, on_resize_internal);
    on_resize_internal(handle_, width, height);

    glfwSetScrollCallback(handle_, on_mouse_scroll_internal);

    make_current();
}

Window::Window(Window&& other)
{
    handle_ = other.handle_;
    scroll_dx_ = other.scroll_dx_;
    scroll_dy_ = other.scroll_dy_;
    glfwSetWindowUserPointer(handle_, this);
    other.handle_ = nullptr;
}

Window& Window::operator=(Window&& other)
{
    handle_ = other.handle_;
    scroll_dx_ = other.scroll_dx_;
    scroll_dy_ = other.scroll_dy_;
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
    auto previous = glfwGetCurrentContext();
    make_current();
    glfwSwapInterval(interval);
    glfwMakeContextCurrent(previous);
    return *this;
}

} // namespace vcl
