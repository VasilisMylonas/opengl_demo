#include "window.hpp"

#include <array>
#include <cstdio>
#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include "gl/buffer.hpp"
#include "gl/program.hpp"
#include "gl/shader.hpp"
#include "gl/vertex_array.hpp"
#include "gl/vertex_layout.hpp"
#include "util.hpp"

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

gl::program load_shaders()
{
    gl::shader vs(gl::shader_type::vertex);
    gl::shader fs(gl::shader_type::fragment);

    vs.set_source(read_file("./shaders/shader.vs"));
    vs.compile();

    fs.set_source(read_file("./shaders/shader.fs"));
    fs.compile();

    gl::program program;
    program.attach(vs);
    program.attach(fs);
    program.link();
    return program;
}

class my_app
{
public:
    gl::vertex_array vao;
    gl::vertex_buffer<glm::vec3> vbo;
    gl::index_buffer<unsigned int> ibo;

    std::array<glm::vec3, 3> vertices = {
        glm::vec3(-0.5f, -0.5f, 0.0f),
        glm::vec3(0.5f, -0.5f, 0.0f),
        glm::vec3(0.0f, 0.5f, 0.0f),
    };

    std::array<unsigned int, 3> indices = {
        0,
        1,
        2,
    };

    bool close = false;

    void load_data()
    {
        vbo.data(vertices.size(), vertices.data(), gl::buffer_usage::static_draw);
        ibo.data(indices.size(), indices.data(), gl::buffer_usage::static_draw);

        gl::vertex_layout layout;
        layout.push_back({
            .stride = sizeof(glm::vec3),
            .offset = 0,
            .type = gl::type_of<glm::vec3>(),
        });

        vao.buffers(vbo, ibo, layout);
    }

    void render()
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        vao.draw(3);

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Load Texture"))
                {
                    // TODO
                }

                if (ImGui::MenuItem("Exit"))
                {
                    close = true;
                }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    }
};

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
        set_font("./fonts/Roboto-Regular.ttf", 18.0f);

        window.show();

        my_app app;
        app.load_data();

        while (!window.should_close() && !app.close)
        {
            gl::program program = load_shaders();
            program.use();

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
