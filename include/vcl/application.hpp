#pragma once

#include "command_line.hpp"
#include "logger.hpp"
#include "window.hpp"

#include <memory>
#include <type_traits>

namespace vcl
{

class Application
{
private:
    Logger logger_;
    CommandLine command_line_;
    static Application* current_;
    static void on_glfw_error(int error, const char* description);

protected:
    virtual void main_loop(Window& window);

public:
    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Window, T>>>
    void start()
    {
        std::unique_ptr<Window> window = std::make_unique<T>();
        window->make_current();
        main_loop(*window);
    }

    static Application& current();
    const CommandLine& command_line() const;
    CommandLine& command_line();
    void poll_events() const;
    Application(int argc, const char* argv[]);
    Application(const Application& other) = delete;
    Application(Application&& other);
    Application& operator=(const Application& other) = delete;
    Application& operator=(Application&& other) = delete; // TODO: move assignment
    virtual ~Application();
    const Logger& logger() const;
};

} // namespace vcl
