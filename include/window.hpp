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

    void resize(int width, int height);
    void close();
    void swap_buffers();
    void make_current();
    void swap_interval(int interval);

    Window(int width, int height, const char *title);
    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;
    Window(Window &&other);
    Window &operator=(Window &&other);
    ~Window();
};