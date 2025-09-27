#include "util.hpp"
#include "window.hpp"

#include <cstdio>
#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float3.hpp>
#include <imgui.h>

#include "gl/buffer.hpp"
#include "gl/program.hpp"
#include "gl/shader.hpp"

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

#include "gl/buffer.hpp"

int main()
{
    glfwSetErrorCallback(glfw_error);

    if (glfwInit() == GLFW_FALSE)
    {
        return EXIT_FAILURE;
    }

    IMGUI_CHECKVERSION();

    {
        Window window(1200, 800, "OpenGL Demo", 4, 0);
        window.swap_interval(1); // Enable vsync

        window.make_current();
        set_font("./fonts/Roboto-Regular.ttf", 18.0f);

        window.show();

        bool close = false;

        glm::vec3 vertices[] = {
            {
                -0.5f,
                -0.5f,
                0.0f,
            },
            {
                0.5f,
                -0.5f,
                0.0f,
            },
            {
                0.0f,
                0.5f,
                0.0f,
            },
        };

        gl::Shader vs(gl::ShaderType::vertex);
        vs.set_source(read_file("./shaders/shader.vs"));
        vs.compile();

        gl::Shader fs(gl::ShaderType::fragment);
        fs.set_source(read_file("./shaders/shader.fs"));
        fs.compile();

        gl::Program program;
        program.attach(vs);
        program.attach(fs);
        program.link();
        program.use();

        gl::ArrayBuffer<glm::vec3> vbo(3, gl::BufferUsage::static_draw);
        gl::IndexBuffer<int> ibo(3, gl::BufferUsage::static_draw);

        ibo.data(3, (int[]){0, 1, 2});
        vbo.data(3, vertices);

        Vertex

        while (!window.should_close() && !close)
        {
            glfwPollEvents();

            // Render for window1
            window.make_current();
            window.begin_frame();

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            if (ImGui::BeginMainMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {
                    if (ImGui::MenuItem("Exit"))
                    {
                        close = true;
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

            window.end_frame();
            window.swap_buffers();
        }
    }

    glfwTerminate();

    return EXIT_SUCCESS;
}
