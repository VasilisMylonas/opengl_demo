#include "gl/uniform.hpp"
#include "window.hpp"

#include <array>
#include <cstdio>
#include <cstdlib>
#include <optional>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

#include "gl/buffer.hpp"
#include "gl/program.hpp"
#include "gl/shader.hpp"
#include "gl/vertex_array.hpp"
#include "gl/vertex_layout.hpp"
#include "util.hpp"

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

class my_app
{
public:
    gl::vertex_array vao_triangle;
    gl::vertex_array vao_square;
    gl::vertex_buffer<glm::vec3> vbo;
    gl::index_buffer<unsigned int> ibo_triangle;
    gl::index_buffer<unsigned int> ibo_square;
    gl::program current_program;

    std::optional<gl::uniform> u_color;
    std::optional<gl::uniform> u_proj;

    std::array<glm::vec3, 7> vertices = {
        // Triangle
        glm::vec3(-0.5f, -0.5f, 0.0f),
        glm::vec3(0.5f, -0.5f, 0.0f),
        glm::vec3(0.0f, 0.5f, 0.0f),

        // Square
        glm::vec3(-0.5f, -0.5f, 0.0f),
        glm::vec3(-0.5f, 0.5f, 0.0f),
        glm::vec3(0.5f, 0.5f, 0.0f),
        glm::vec3(0.5f, -0.5f, 0.0f),
    };

    std::array<unsigned int, 3> indices_triangle = {
        0,
        1,
        2,
    };

    std::array<unsigned int, 6> indices_square = {
        3,
        4,
        5,
        5,
        6,
        3,
    };

    bool close = false;
    int shape_selected = 0;

    glm::vec3 vertex_color = {0.0f, 0.0f, 0.0f};
    glm::vec3 clear_color = {1.0f, 1.0f, 1.0f};

    void load_data()
    {
        vbo.data(vertices.size(), vertices.data(), gl::buffer_usage::static_draw);
        ibo_triangle.data(
            indices_triangle.size(), indices_triangle.data(), gl::buffer_usage::static_draw);
        ibo_square.data(
            indices_square.size(), indices_square.data(), gl::buffer_usage::static_draw);

        gl::vertex_layout layout;
        layout.push_back({
            .stride = sizeof(glm::vec3),
            .offset = 0,
            .type = gl::type_of<glm::vec3>(),
        });

        vao_square.buffers(vbo, ibo_square, layout);
        vao_triangle.buffers(vbo, ibo_triangle, layout);
    }

    void load_shaders()
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
        program.use();

        current_program = std::move(program);

        load_uniforms();
    }

    void load_uniforms()
    {
        u_color = current_program.uniform("u_color");
        u_proj = current_program.uniform("u_proj");
    }

    void render()
    {
        glClearColor(clear_color.r, clear_color.g, clear_color.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (shape_selected == 0)
        {
            vao_triangle.draw();
        }
        else if (shape_selected == 1)
        {
            vao_square.draw();
        }
        else if (shape_selected == 2)
        {
            // TODO: circle
        }

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Reload Shaders"))
                {
                    load_shaders();
                }

                if (ImGui::BeginMenu("Shape"))
                {
                    const char* shapes[] = {"Triangle", "Square", "Circle"};

                    for (int i = 0; i < 3; ++i)
                    {
                        if (ImGui::MenuItem(shapes[i], nullptr, shape_selected == i))
                        {
                            shape_selected = i;
                        }
                    }
                    ImGui::EndMenu();
                }

                if (ImGui::MenuItem("Exit"))
                {
                    close = true;
                }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

        if (ImGui::Begin("Color Selection"))
        {
            ImGui::ColorEdit3("Background Color", glm::value_ptr(clear_color));

            if (ImGui::ColorEdit3("Foreground Color", glm::value_ptr(vertex_color)))
            {
                u_color->set(vertex_color);
            }
        }
        ImGui::End(); // This needs to be outside `if`
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
        app.load_shaders();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(opengl_message, nullptr);

        while (!window.should_close() && !app.close)
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
