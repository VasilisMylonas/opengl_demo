#include <cstdio>
#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include "my_app.hpp"
#include "window.hpp"

void opengl_message([[maybe_unused]] GLenum source,
                    GLenum type,
                    [[maybe_unused]] GLuint id,
                    GLenum severity,
                    [[maybe_unused]] GLsizei length,
                    const GLchar* message,
                    [[maybe_unused]] const void* userParam)
{
    fprintf(stderr,
            "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
            type,
            severity,
            message);
}

void glfw_error([[maybe_unused]] int error, const char* description)
{
    fprintf(stderr, "GLFW Error: %s\n", description);
}

void set_font(const char* font_path, float font_size)
{
    auto& io = ImGui::GetIO();
    ImFont* font = io.Fonts->AddFontFromFileTTF(font_path, font_size);
    if (!font)
    {
        fprintf(stderr, "Failed to load font from %s!\n", font_path);
    }
}



int main()
{
    glfwSetErrorCallback(glfw_error);

    if (glfwInit() == GLFW_FALSE)
    {
        return EXIT_FAILURE;
    }

    IMGUI_CHECKVERSION();

    {
        window window(1200, 800, "OpenGL Demo", 4, 0);
        window.swap_interval(1); // Enable vsync
        window.make_current();
        set_font("./res/fonts/Roboto-Regular.ttf", 18.0f);

        window.show();

        my_app app;
        app.init();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(opengl_message, nullptr);

        while (!window.should_close() && !app.should_close())
        {
            glfwPollEvents();

            window.begin_frame();
            app.render();
            window.end_frame();

            window.swap_buffers();
        }
    }

    glfwTerminate();

    return EXIT_SUCCESS;
}
