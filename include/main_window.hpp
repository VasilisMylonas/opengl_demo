#pragma once

#include <array>

#include "gl/buffer.hpp"
#include "gl/program.hpp"
#include "gl/renderer.hpp"
#include "gl/shader.hpp"
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

    vcl::FpsCounter counter{};
    vcl::Timer timer{};

    std::array<gl::Vertex, 4> vertices = {
        gl::Vertex{
            .position = {0, 1, 0},
            .color = {1, 0, 0, 1},
        },
        gl::Vertex{
            .position = {1, -1, 0},
            .color = {0, 1, 0, 1},
        },
        gl::Vertex{
            .position = {-1, -1, 0},
            .color = {0, 0, 1, 1},
        },
        gl::Vertex{
            .position = {-1, -1, 0},
            .color = {1, 0, 1, 1},
        },
    };

    std::array<unsigned int, 3> indices = {
        0,
        1,
        2,
    };

    void reload_shaders()
    {
        gl::Shader fs{gl::Shader::Type::FRAGMENT};
        gl::Shader vs{gl::Shader::Type::VERTEX};
        fs.source_path("../shaders/shader.fs").compile();
        vs.source_path("../shaders/shader.vs").compile();

        gl::Program program{};
        program.attach(vs).attach(fs).link().use().detach(fs).detach(vs);
    }

public:
    virtual void render() override
    {
        gl::Renderer::clear();

        vcl::Application::current().logger().info("%.2lffps", counter.fps());

        if (timer.delta() > 1)
        {
            reload_shaders();
            timer.reset();
        }

        gl::Renderer::draw(vao, 3);
    }

    MainWindow() : Window{1000, 400, "Pong"}
    {
        gl::Renderer::enable_blending();

        reload_shaders();

        vao.buffers(vbo, ibo);
        vbo.data(4, vertices.data());
        ibo.data(3, indices.data());
    }
};
