#include "window.hpp"

#include <cstdio>
#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

void glfw_error([[maybe_unused]] int error, const char* description)
{
    fprintf(stderr, "GLFW Error: %s\n", description);
}

void render(Window& window)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit"))
            {
                // You might want to set a flag to close the window here
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help"))
        {
            ImGui::MenuItem("About");
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void imgui_pre_render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void imgui_post_render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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
        Window window1(1200, 800, "OpenGL Demo", 4, 0);
        window1.swap_interval(1); // Enable vsync

        Window window2(800, 600, "Second Window", 4, 0);
        window2.swap_interval(1); // Enable vsync

        window1.make_current();
        set_font("./fonts/Roboto-Regular.ttf", 18.0f);

        window2.make_current();
        set_font("./fonts/Roboto-Regular.ttf", 18.0f);

        window1.show();
        window2.show();

        while (!window1.should_close() && !window2.should_close())
        {
            glfwPollEvents();

            // Render for window1
            window1.make_current();
            imgui_pre_render();
            render(window1);
            imgui_post_render();
            window1.swap_buffers();

            // Render for window2
            window2.make_current();
            imgui_pre_render();
            render(window2);
            imgui_post_render();
            window2.swap_buffers();
        }
    }

    glfwTerminate();

    return EXIT_SUCCESS;
}
