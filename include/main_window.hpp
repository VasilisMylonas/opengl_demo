#pragma once

#include <array>
#include <optional>

#include "gl/buffer.hpp"
#include "gl/program.hpp"
#include "gl/renderer.hpp"
#include "gl/shader.hpp"
#include "gl/texture.hpp"
#include "gl/uniform.hpp"
#include "gl/vertex.hpp"
#include "gl/vertex_array.hpp"

#include "vcl/application.hpp"
#include "vcl/fps_counter.hpp"
#include "vcl/timer.hpp"
#include "vcl/window.hpp"

class MainWindow : public vcl::Window
{
private:
    gl::VertexBuffer vbo{4, gl::BufferUsage::DYNAMIC_DRAW};
    gl::IndexBuffer ibo{6, gl::BufferUsage::DYNAMIC_DRAW};
    gl::VertexArray vao{};
    gl::Texture tex{};
    gl::Program program{};
    std::optional<gl::Uniform> u_texture;

    vcl::FpsCounter counter{};
    vcl::Timer timer{};

    std::array<gl::Vertex, 4> vertices = {
        gl::Vertex{
            .position = {0.5, 0.5, 0},
            .color = {1, 1, 1, 1},
            .uv = {1, 1},
        },
        gl::Vertex{
            .position = {0.5, -0.5, 0},
            .color = {1, 1, 1, 1},
            .uv = {1, 0},
        },
        gl::Vertex{
            .position = {-0.5, -0.5, 0},
            .color = {1, 1, 1, 1},
            .uv = {0, 0},
        },
        gl::Vertex{
            .position = {-0.5, 0.5, 0},
            .color = {1, 1, 1, 1},
            .uv = {0, 1},
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
        gl::Shader fs{gl::Shader::Type::FRAGMENT};
        gl::Shader vs{gl::Shader::Type::VERTEX};
        fs.source_path("../shaders/shader.fs").compile();
        vs.source_path("../shaders/shader.vs").compile();

        program.attach(vs).attach(fs).link().use().detach(fs).detach(vs);
        u_texture = program.uniform("u_texture");
    }

    void load_textures()
    {
        tex.source_path("../image.png");
    }

public:
    virtual void render() override
    {
        gl::Renderer::clear();

        vcl::Application::current().logger().info("%.2lffps", counter.fps());

        if (timer.delta() > 1)
        {
            load_shaders();
            timer.reset();
        }

        GL_CALL(glActiveTexture(GL_TEXTURE0 + 0));
        tex.bind();
        u_texture->set(0);
        gl::Renderer::draw(vao, 6);
        tex.unbind();
    }

    MainWindow() : Window{1000, 400, "Pong"}
    {
        gl::Renderer::enable_blending();

        load_shaders();
        load_textures();

        vao.buffers(vbo, ibo);
        vbo.data(4, vertices.data());
        ibo.data(6, indices.data());
    }
};
