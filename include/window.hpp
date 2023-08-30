#pragma once

#include <utility>

typedef struct GLFWwindow GLFWwindow;

class Window
{
private:
    GLFWwindow *handle_;

    static Window *get_wrapper(GLFWwindow *handle);

public:
    std::pair<int, int> size() const;
    bool should_close() const;
    bool current() const;

    void resize(int width, int height);
    void close();
    void swap_buffers();
    void make_current();

    Window(int width, int height, const char *title);
    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;
    Window(Window &&other);
    Window &operator=(Window &&other);
    ~Window();
};