#include "window.hpp"

#include <GL//glew.h> // Must come before GLFW
#include <GLFW/glfw3.h>

#include <functional>
#include <stdexcept>

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

void Window::on_mouse_scroll_internal(GLFWwindow* window, double x_offset, double y_offset)
{
    auto self = get_wrapper(window);
    self->scroll_delta_ = {x_offset, y_offset};
}

void Window::on_resize_internal(GLFWwindow* window, int width, int height)
{
    with_context(window, [width, height]() { glViewport(0, 0, width, height); });
}

void Window::make_current()
{
    glfwMakeContextCurrent(handle_);

    // TODO: is this needed every time?
    glewExperimental = GL_TRUE;

    auto code = glewInit();
    if (code != GLEW_OK)
    {
        throw std::runtime_error(reinterpret_cast<const char*>(glewGetErrorString(code)));
    }
}

Window::Window(int width, int height, const char* title, int opengl_major_version, int opengl_minor_version) : scroll_delta_{0, 0}
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, opengl_major_version);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, opengl_minor_version);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    // TODO: anti-aliasing
    glfwWindowHint(GLFW_SAMPLES, 16);

    handle_ = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!handle_)
    {
        const char* msg;
        glfwGetError(&msg);
        throw std::runtime_error(msg);
    }

    glfwSetWindowUserPointer(handle_, this);

    glfwSetFramebufferSizeCallback(handle_, on_resize_internal);
    glfwSetScrollCallback(handle_, on_mouse_scroll_internal);

    on_resize_internal(handle_, width, height);
}

Window::~Window()
{
    if (handle_)
    {
        glfwDestroyWindow(handle_);
    }
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

bool Window::current() const
{
    return glfwGetCurrentContext() == handle_;
}

bool Window::should_close() const
{
    return glfwWindowShouldClose(handle_);
}

std::pair<int, int> Window::scroll_delta() const
{
    auto value = scroll_delta_;
    scroll_delta_ = {0, 0};
    return value;
}

void Window::swap_interval(int interval)
{
    with_context(handle_, [interval]() { glfwSwapInterval(interval); });
}

void Window::swap_buffers()
{
    glfwSwapBuffers(handle_);
}

void Window::resize(int width, int height)
{
    glfwSetWindowSize(handle_, width, height);
}

void Window::close()
{
    glfwSetWindowShouldClose(handle_, true);
}

void Window::show()
{
    glfwShowWindow(handle_);
}

void Window::hide()
{
    glfwHideWindow(handle_);
}

void Window::attention()
{
    glfwRequestWindowAttention(handle_);
}

void Window::restore()
{
    glfwRestoreWindow(handle_);
}

void Window::minimize()
{
    glfwIconifyWindow(handle_);
}

void Window::maximize()
{
    glfwMaximizeWindow(handle_);
}

void Window::focus()
{
    glfwFocusWindow(handle_);
}
