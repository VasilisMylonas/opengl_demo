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
