#pragma once

#include <stdexcept>
#include <utility>

// From GLFW
typedef struct GLFWwindow GLFWwindow;

namespace vcl
{

class Window
{
private:
    GLFWwindow* handle_;
    double scroll_dx_;
    double scroll_dy_;

    static void on_resize_internal(GLFWwindow* window, int width, int height);
    static void on_mouse_scroll_internal(GLFWwindow* window, double x_offset, double y_offset);

protected:
    GLFWwindow* handle() const;

public:
    class ContextException : public std::runtime_error
    {
    public:
        ContextException(const char* msg) : runtime_error{msg}
        {
        }
    };

    class CreationException : public std::runtime_error
    {
    public:
        CreationException(const char* msg) : runtime_error{msg}
        {
        }
    };

    virtual void render() = 0;

    std::pair<int, int> size() const;
    std::pair<double, double> scroll() const;
    bool should_close() const;
    bool current() const;

    Window& resize(int width, int height);
    Window& close();
    Window& focus();
    Window& maximize();
    Window& minimize();
    Window& restore();
    Window& attention();
    Window& show();
    Window& hide();
    Window& swap_buffers();
    Window& make_current();
    Window& swap_interval(int interval);

    Window(int width, int height, const char* title);
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    Window(Window&& other);
    Window& operator=(Window&& other);
    virtual ~Window();
};

} // namespace vcl
