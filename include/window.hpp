// This is a simple wrapper around GLFWwindow

#pragma once

#include <utility>

// From GLFW
typedef struct GLFWwindow GLFWwindow;

class Window
{
public:
    GLFWwindow* handle() const;

    std::pair<int, int> size() const;
    std::pair<int, int> scroll_delta() const;
    bool should_close() const;
    bool current() const;

    void resize(int width, int height);
    void close();
    void focus();
    void maximize();
    void minimize();
    void restore();
    void attention();
    void show();
    void hide();

    void swap_buffers();
    void make_current();
    void swap_interval(int interval);

    Window(int width,
           int height,
           const char* title,
           int opengl_major_version = 3,
           int opengl_minor_version = 3);
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    Window(Window&& other);
    Window& operator=(Window&& other);
    virtual ~Window();

private:
    GLFWwindow* handle_;
    mutable std::pair<int, int> scroll_delta_;

    static void on_resize_internal(GLFWwindow* window, int width, int height);
    static void on_mouse_scroll_internal(GLFWwindow* window, double x_offset, double y_offset);
};
