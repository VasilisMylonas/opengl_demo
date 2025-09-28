#include "util.hpp"
#include "window.hpp"

#include <array>
#include <cstdio>
#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float3.hpp>
#include <imgui.h>

#include "gl/buffer.hpp"
#include "gl/program.hpp"
#include "gl/shader.hpp"
#include "gl/vertex_array.hpp"
#include "gl/vertex_layout.hpp"

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
        Window window(1200, 800, "OpenGL Demo", 4, 0);
        window.swap_interval(1); // Enable vsync

        window.make_current();
        set_font("./fonts/Roboto-Regular.ttf", 18.0f);

        window.show();

        bool close = false;

        std::array<glm::vec3, 3> vertices = {
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

        std::array<int, 3> indices = {
            0,
            1,
            2,
        };

        gl::shader vs(gl::shader_type::vertex);
        vs.set_source(read_file("./shaders/shader.vs"));
        vs.compile();

        gl::shader fs(gl::shader_type::fragment);
        fs.set_source(read_file("./shaders/shader.fs"));
        fs.compile();

        gl::program program;
        program.attach(vs);
        program.attach(fs);
        program.link();
        program.use();

        gl::array_buffer<glm::vec3> vbo(vertices.size(), gl::buffer_usage::static_draw);
        gl::index_buffer<int> ibo(indices.size(), gl::buffer_usage::static_draw);

        ibo.data(indices.size(), indices.data());
        vbo.data(vertices.size(), vertices.data());

        gl::vertex_layout layout;
        layout.push_back({
            .stride = sizeof(glm::vec3),
            .offset = 0,
            .type = gl::type_of<glm::vec3>(),
        });

        gl::VertexArray vao;
        vao.buffers(vbo, ibo, layout);

        while (!window.should_close() && !close)
        {
            glfwPollEvents();

            // Render for window1
            window.make_current();
            window.begin_frame();

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            vao.bind();
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
            vao.unbind();

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
