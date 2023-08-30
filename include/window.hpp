#pragma once

#include "GLFW/glfw3.h"
#include "GL/glew.h"

#include <utility>

class Window
{
private:
    GLFWwindow *handle_;

    static Window *get_wrapper(GLFWwindow *handle)
    {
        return static_cast<Window *>(glfwGetWindowUserPointer(handle));
    }

    static void on_resize_internal(GLFWwindow *window, int width, int height)
    {
        (void)window;
        glViewport(0, 0, width, height);
    }

public:
    std::pair<int, int> size() const
    {
        int width, height;
        glfwGetWindowSize(handle_, &width, &height);
        return {width, height};
    }

    void resize(int width, int height)
    {
        glfwSetWindowSize(handle_, width, height);
    }

    bool should_close() const
    {
        return glfwWindowShouldClose(handle_);
    }

    void close()
    {
        glfwSetWindowShouldClose(handle_, GLFW_TRUE);
    }

    void swap_buffers()
    {
        glfwSwapBuffers(handle_);
    }

    void make_current()
    {
        glfwMakeContextCurrent(handle_);
    }

    bool current() const
    {
        return glfwGetCurrentContext() == handle_;
    }

    Window(int width, int height, const char *title)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;

    Window(Window &&other)
    {
        handle_ = other.handle_;
        glfwSetWindowUserPointer(handle_, this);
        other.handle_ = nullptr;
    }

    Window &operator=(Window &&other)
    {
        handle_ = other.handle_;
        glfwSetWindowUserPointer(handle_, this);
        other.handle_ = nullptr;
        return *this;
    }

    ~Window()
    {
        if (handle_)
        {
            glfwDestroyWindow(handle_);
        }
    }
};