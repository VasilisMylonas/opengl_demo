#pragma once

#include "app.hpp"

#include "util.hpp"

#include <array>
#include <optional>

#include "gl/buffer.hpp"
#include "gl/program.hpp"
#include "gl/shader.hpp"
#include "gl/texture.hpp"
#include "gl/uniform.hpp"
#include "gl/vertex_array.hpp"
#include "gl/vertex_layout.hpp"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ImGuiFileDialog.h>
#include <imgui.h>

struct vertex
{
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 texture_coords = {0.0f, 0.0f};
};

class my_app : public app
{
public:
    virtual void init() override;
    virtual void render() override;
    virtual bool should_close() override;

private:
    gl::vertex_array vao_0;
    gl::vertex_array vao_1;
    gl::vertex_array vao_2;
    gl::vertex_buffer<vertex> vbo;
    gl::index_buffer<unsigned int> ibo_0;
    gl::index_buffer<unsigned int> ibo_1;
    gl::index_buffer<unsigned int> ibo_2;
    gl::program current_program;
    gl::texture current_texture;

    std::optional<gl::uniform> u_color;
    std::optional<gl::uniform> u_mvp;
    std::optional<gl::uniform> u_texture;
    std::optional<gl::uniform> u_use_texture;

    std::array<vertex, 13> vertices = {
        vertex{
            glm::vec3(-0.5f, -0.5f, -0.5f), // Bottom-Back-Left
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
        },
        vertex{
            glm::vec3(0.5f, -0.5f, -0.5f), // Bottom-Back-Right
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
        },
        vertex{
            glm::vec3(0.5f, 0.5f, -0.5f), // Top-Back-Right
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
        },
        vertex{
            glm::vec3(-0.5f, 0.5f, -0.5f), // Top-Back-Left
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
        },
        vertex{
            glm::vec3(-0.5f, -0.5f, 0.5f), // Bottom-Front-Left
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
        },
        vertex{
            glm::vec3(0.5f, -0.5f, 0.5f), // Bottom-Front-Right
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
        },
        vertex{
            glm::vec3(0.5f, 0.5f, 0.5f), // Top-Front-Right
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
        },
        vertex{
            glm::vec3(-0.5f, 0.5f, 0.5f), // Top-Front-Left
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
        },
        vertex{
            glm::vec3(0.0f, 0.5f, 0.0f), // Pyramid Top
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
        },

        vertex{
            glm::vec3(-0.5f, -0.5f, 0.0f), // Bottom-Left
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            glm::vec2(0.0f, 0.0f),
        },
        vertex{
            glm::vec3(0.5f, -0.5f, 0.0f), // Bottom-Right
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            glm::vec2(1.0f, 0.0f),
        },
        vertex{
            glm::vec3(0.5f, 0.5f, 0.0f), // Top-Right
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            glm::vec2(1.0f, 1.0f),
        },
        vertex{
            glm::vec3(-0.5f, 0.5f, 0.0f), // Top-Left
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            glm::vec2(0.0f, 1.0f),
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

    std::array<unsigned int, 6> indices_2 = {
        9,
        10,
        11,
        9,
        11,
        12,
    };

    bool close = false;
    int shape_selected = 1;

    glm::vec3 vertex_color = {1.0f, 0.5f, 0.5f};
    glm::vec3 clear_color = {1.0f, 1.0f, 1.0f};

    void load_data();
    void load_shaders();
    void load_uniforms();
    void render_gui();
    void draw_shape(gl::vertex_array& vao);
    void draw_outline(gl::vertex_array& vao);
    void draw_points(gl::vertex_array& vao);
};
