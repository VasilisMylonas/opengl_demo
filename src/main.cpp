#include "gl/uniform.hpp"
#include "glm/ext/quaternion_transform.hpp"
#include "window.hpp"

#include <array>
#include <cstdio>
#include <cstdlib>
#include <glm/ext/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
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

struct vertex
{
    glm::vec3 position;
    glm::vec3 color;
};

class my_app
{
public:
    gl::vertex_array vao_0;
    gl::vertex_array vao_1;
    gl::vertex_buffer<vertex> vbo;
    gl::index_buffer<unsigned int> ibo_0;
    gl::index_buffer<unsigned int> ibo_1;
    gl::program current_program;

    std::optional<gl::uniform> u_color;
    std::optional<gl::uniform> u_mvp;

    std::array<vertex, 9> vertices = {
        vertex{
            glm::vec3(-0.5f, -0.5f, -0.5f), // Bottom-Back-Left
            glm::vec3(1.0f, 0.0f, 0.0f)     // Red
        },
        vertex{
            glm::vec3(0.5f, -0.5f, -0.5f), // Bottom-Back-Right
            glm::vec3(0.0f, 1.0f, 0.0f)    // Green
        },
        vertex{
            glm::vec3(0.5f, 0.5f, -0.5f), // Top-Back-Right
            glm::vec3(0.0f, 0.0f, 1.0f)   // Blue
        },
        vertex{
            glm::vec3(-0.5f, 0.5f, -0.5f), // Top-Back-Left
            glm::vec3(1.0f, 1.0f, 0.0f)    // Yellow
        },
        vertex{
            glm::vec3(-0.5f, -0.5f, 0.5f), // Bottom-Front-Left
            glm::vec3(1.0f, 0.0f, 1.0f)    // Magenta
        },
        vertex{
            glm::vec3(0.5f, -0.5f, 0.5f), // Bottom-Front-Right
            glm::vec3(0.0f, 1.0f, 1.0f)   // Cyan
        },
        vertex{
            glm::vec3(0.5f, 0.5f, 0.5f), // Top-Front-Right
            glm::vec3(0.5f, 0.5f, 0.5f)  // Gray
        },
        vertex{
            glm::vec3(-0.5f, 0.5f, 0.5f), // Top-Front-Left
            glm::vec3(1.0f, 0.5f, 0.0f)   // Orange
        },
        vertex{
            glm::vec3(0.0f, 0.5f, 0.0f), // Pyramid Top
            glm::vec3(0.5f, 0.0f, 0.5f)  // Purple
        },
    };

    std::array<unsigned int, 30> indices_0 = {
        0,
        1,
        4,
        1,
        4,
        5, // Base
        0,
        4,
        8, // Left
        1,
        5,
        8, // Right
        0,
        1,
        8, // Back,
        4,
        5,
        8 // Front

    };

    std::array<unsigned int, 36> indices_1 = {
        0, 1, 2, 2, 3, 0, // back face
        4, 5, 6, 6, 7, 4, // front face
        4, 5, 1, 1, 0, 4, // bottom face
        7, 6, 2, 2, 3, 7, // top face
        4, 0, 3, 3, 7, 4, // left face
        5, 1, 2, 2, 6, 5  // right face
    };

    bool close = false;
    int shape_selected = 1;

    glm::vec3 vertex_color = {0.0f, 0.0f, 0.0f};
    glm::vec3 clear_color = {1.0f, 1.0f, 1.0f};

    void load_data()
    {
        vbo.data(vertices.size(), vertices.data(), gl::buffer_usage::static_draw);
        ibo_0.data(indices_0.size(), indices_0.data(), gl::buffer_usage::static_draw);
        ibo_1.data(indices_1.size(), indices_1.data(), gl::buffer_usage::static_draw);

        gl::vertex_layout layout;
        layout.push_back(VERTEX_ATTRIBUTE(vertex, position));
        layout.push_back(VERTEX_ATTRIBUTE(vertex, color));

        vao_0.buffers(vbo, ibo_0, layout);
        vao_1.buffers(vbo, ibo_1, layout);
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
        u_mvp = current_program.uniform("u_mvp");
    }

    void render()
    {
        // Model
        float angle = static_cast<float>(glfwGetTime()) * 50;
        glm::mat4 model =
            glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

        // View
        glm::mat4 view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), // camera position
                                     glm::vec3(0.0f, 0.0f, 0.0f), // target
                                     glm::vec3(0.0f, 1.0f, 0.0f)  // up vector
        );

        int viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        int windowWidth = viewport[2];
        int windowHeight = viewport[3];

        // Projection
        glm::mat4 projection =
            glm::perspective(glm::radians(45.0f),                      // FOV
                             (float)windowWidth / (float)windowHeight, // Aspect Ratio
                             0.1f,
                             100.0f);

        // MVP
        glm::mat4 mvp = projection * view * model;

        u_mvp->set(mvp);

        glClearColor(clear_color.r, clear_color.g, clear_color.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (shape_selected == 0)
        {
            vao_0.draw();
        }
        else if (shape_selected == 1)
        {
            vao_1.draw();
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
                    std::array<const char*, 2> shapes = {"Pyramid", "Cube"};

                    for (int i = 0; i < shapes.size(); ++i)
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
