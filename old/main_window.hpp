#pragma once

#include <array>
#include <optional>

#include "gl/buffer.hpp"
#include "gl/program.hpp"
#include "gl/renderer.hpp"
#include "gl/shader.hpp"
#include "gl/texture.hpp"
#include "gl/uniform.hpp"
#include "gl/vertex_array.hpp"
#include "gl/vertex_layout.hpp"

#include "vcl/application.hpp"
#include "vcl/fps_counter.hpp"
#include "vcl/timer.hpp"
#include "vcl/window.hpp"

#include "vertex.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

gl::VertexBuffer<vertex> vbo{4, gl::buffer_usage::dynamic_draw};
gl::IndexBuffer ibo{6, gl::BufferUsage::dynamic_draw};
gl::VertexArray vao{};
gl::Texture tex{0};
gl::program program{};
std::optional<gl::uniform> u_textures{};
std::optional<gl::uniform> u_proj{};

vcl::FpsCounter counter{};
vcl::Timer timer{};

std::array<vertex, 4> vertices = {
    Vertex{
        .position = {0.5, 0.5, 0},
        .color = {1, 0, 0, 1},
        .uv = {1, 1},
        .texture = 0,
    },
    Vertex{
        .position = {0.5, -0.5, 0},
        .color = {0, 1, 0, 1},
        .uv = {1, 0},
        .texture = 0,
    },
    Vertex{
        .position = {-0.5, -0.5, 0},
        .color = {0, 0, 1, 1},
        .uv = {0, 0},
        .texture = 0,
    },
    Vertex{
        .position = {-0.5, 0.5, 0},
        .color = {1, 0, 1, 1},
        .uv = {0, 1},
        .texture = 0,
    },
};

std::array<unsigned int, 6> indices = {
    0,
    1,
    2,
    2,
    3,
    0,
};

void load_shaders()
{
    gl::shader fs{gl::Shader::shader_type::fragment};
    gl::shader vs{gl::Shader::shader_type::vertex};
    fs.source_path("../shaders/shader.fs").compile();
    vs.source_path("../shaders/shader.vs").compile();

    program.attach(vs).attach(fs).link().use().detach(fs).detach(vs);
    u_textures = program.uniform("u_textures");
    u_proj = program.uniform("u_proj");
    int tmp[] = {static_cast<int>(tex.slot()), 0};
    u_textures->set(2, tmp);
}

void load_textures()
{
    tex.source_path("../op.jpeg");
}

float rotation = 0;
glm::vec3 translation{0, 0, 0};

// (0.0, 1.0]
float sensitivity = 0.5f;

virtual void render() override
{
    auto [dx, dy] = scroll();
    translation.x += (float)dx * sensitivity;
    translation.y += (float)dy * sensitivity;

    gl::Renderer::clear();

    glm::mat4 model{1};
    glm::vec3 axis{0, 0, 1};
    glm::mat4 proj = glm::rotate(model, rotation, axis);
    glm::mat4 trans = glm::translate(model, translation);

    u_proj->set(proj * trans);

    vcl::Application::current().logger().info("%.2lffps", counter.fps());
    rotation += 0.01f;

    // if (timer.delta() > 1)
    // {
    //     load_shaders();
    //     timer.reset();
    // }

    gl::Renderer::draw_texture(tex, vao, 6);
}

gl::Renderer::enable_blending();

load_shaders();
load_textures();

vao.buffers(vbo, ibo, Vertex::layout());
vbo.data(4, vertices.data());
ibo.data(6, indices.data());

swap_interval(1);
