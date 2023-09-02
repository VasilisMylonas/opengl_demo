#pragma once

#include <utility>

class Window
{
private:
    typedef struct GLFWwindow GLFWwindow;
    GLFWwindow *handle_;

public:
    std::pair<int, int> size() const;
    bool should_close() const;
    bool current() const;

    Window &resize(int width, int height);
    Window &close();
    Window &focus();
    Window &maximize();
    Window &minimize();
    Window &restore();
    Window &attention();
    Window &show();
    Window &hide();
    Window &swap_buffers();
    Window &make_current();
    Window &swap_interval(int interval);

    Window(int width, int height, const char *title);
    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;
    Window(Window &&other);
    Window &operator=(Window &&other);
    ~Window();
};