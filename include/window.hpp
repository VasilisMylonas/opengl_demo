// This is a simple wrapper around GLFWwindow with optional ImGui integration.

#pragma once

#include <functional>
#include <utility>

#define IMGUI_INTEGRATION 1

// From GLFW
typedef struct GLFWwindow GLFWwindow;

#if IMGUI_INTEGRATION
typedef struct ImGuiContext ImGuiContext;
#endif

class window
{
public:
    GLFWwindow* handle() const;

#if IMGUI_INTEGRATION
    ImGuiContext* context() const;
#endif

    std::pair<int, int> size() const;
    std::pair<int, int> scroll_delta() const;
    bool should_close() const;
    bool is_current() const;

    void resize(int width, int height);
    void close();
    void focus();
    void maximize();
    void minimize();
    void restore();
    void attention();
    void show();
    void hide();

    void make_current();
    void begin_frame();
    void end_frame();
    void swap_buffers();
    void swap_interval(int interval);

    void with_context(std::function<void()> function);

    window(int width,
           int height,
           const char* title,
           int opengl_major_version = 3,
           int opengl_minor_version = 3);
    window(const window&) = delete;
    window& operator=(const window&) = delete;
    window(window&& other);
    window& operator=(window&& other);
    virtual ~window();

private:
    GLFWwindow* handle_;
#if IMGUI_INTEGRATION
    ImGuiContext* context_;
#endif
    mutable std::pair<int, int> scroll_delta_;

    static void on_resize_internal(GLFWwindow* window, int width, int height);
    static void on_mouse_scroll_internal(GLFWwindow* window, double x_offset, double y_offset);
};
