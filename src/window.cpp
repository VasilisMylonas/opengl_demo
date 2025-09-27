#include "window.hpp"
#include <stdexcept>

#include <GL/glew.h> // Must come before GLFW
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

static Window* get_wrapper(GLFWwindow* handle)
{
    return static_cast<Window*>(glfwGetWindowUserPointer(handle));
}

void Window::with_context(std::function<void()> function)
{
    auto g = glfwGetCurrentContext();

    if (!g)
    {
        make_current();
        function();
        glfwMakeContextCurrent(NULL);
        return;
    }

    auto previous = get_wrapper(g);
    make_current();
    function();
    previous->make_current();
}

void Window::begin_frame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Window::end_frame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Window::on_mouse_scroll_internal(GLFWwindow* window, double x_offset, double y_offset)
{
    auto self = get_wrapper(window);
    self->scroll_delta_ = {x_offset, y_offset};
}

void Window::on_resize_internal(GLFWwindow* window, int width, int height)
{
    auto self = get_wrapper(window);
    self->with_context([width, height]() { glViewport(0, 0, width, height); });
}

void Window::make_current()
{
    glfwMakeContextCurrent(handle_);
    ImGui::SetCurrentContext(context_);

    // TODO: is this needed every time?
    glewExperimental = GL_TRUE;

    auto code = glewInit();
    if (code != GLEW_OK)
    {
        throw std::runtime_error(reinterpret_cast<const char*>(glewGetErrorString(code)));
    }
}

Window::Window(
    int width, int height, const char* title, int opengl_major_version, int opengl_minor_version)
    : scroll_delta_{0, 0}
{
    // Creat GLFW window
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

    // For get_wrapper function
    glfwSetWindowUserPointer(handle_, this);

    // Register callbacks
    glfwSetFramebufferSizeCallback(handle_, on_resize_internal);
    glfwSetScrollCallback(handle_, on_mouse_scroll_internal);

    // Create ImGui context
    context_ = ImGui::CreateContext();

    with_context(
        [this]()
        {
            ImGui_ImplOpenGL3_Init();
            ImGui_ImplGlfw_InitForOpenGL(handle_, true);
        });

    // Set size
    on_resize_internal(handle_, width, height);
}

Window::~Window()
{
    if (!handle_)
    {
        return;
    }

    with_context(
        []()
        {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
        });

    ImGui::DestroyContext(context_);
    glfwDestroyWindow(handle_);
    handle_ = nullptr;
}

Window::Window(Window&& other)
{
    handle_ = other.handle_;
    context_ = other.context_;
    scroll_delta_ = other.scroll_delta_;
    glfwSetWindowUserPointer(handle_, this);
    other.handle_ = nullptr;
    other.context_ = nullptr;
}

Window& Window::operator=(Window&& other)
{
    this->~Window();
    handle_ = other.handle_;
    context_ = other.context_;
    scroll_delta_ = other.scroll_delta_;
    glfwSetWindowUserPointer(handle_, this);
    other.handle_ = nullptr;
    other.context_ = nullptr;
    return *this;
}

GLFWwindow* Window::handle() const
{
    return handle_;
}

ImGuiContext* Window::context() const
{
    return context_;
}

std::pair<int, int> Window::size() const
{
    int width, height;
    glfwGetWindowSize(handle_, &width, &height);
    return {width, height};
}

bool Window::is_current() const
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
    with_context([interval]() { glfwSwapInterval(interval); });
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
