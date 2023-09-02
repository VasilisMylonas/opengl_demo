#include <iostream>
#include <memory>
#include <array>

#include "config.hpp"

#include "vertex.hpp"
#include "application_base.hpp"
#include "fps_counter.hpp"
#include "renderer.hpp"

#include "gl/shader.hpp"
#include "gl/program.hpp"
#include "gl/buffer.hpp"
#include "gl/vertex_array.hpp"

using namespace gl;

class Application : public ApplicationBase
{
private:
    std::unique_ptr<Buffer> vbo;
    std::unique_ptr<Buffer> ibo;
    // std::unique_ptr<VertexArray> vao;
    // std::unique_ptr<VertexLayout> layout;

    FpsCounter counter{};
    Timer timer{};

    std::array<Vertex, 3> points = {
        Vertex{
            0.0f,
            0.5f,
            0.0f,
        },
        Vertex{
            0.5f,
            -0.5f,
            0.0f,
        },
        Vertex{
            -0.5f,
            -0.5f,
            0.0f,
        },
    };

    std::array<unsigned int, 6> indices = {
        0,
        1,
        1,
        2,
        2,
        0,
    };

protected:
    virtual Window init() override
    {
        Window window{1000, 400, name().c_str()};
        window.make_current();

        Shader fs{Shader::Type::FRAGMENT};
        Shader vs{Shader::Type::VERTEX};
        fs.set_source(fragment_shader).compile();
        vs.set_source(vertex_shader).compile();

        Program program{};
        program.attach(fs).attach(vs).link().use();

        vbo = std::make_unique<Buffer>(points.size(), points.data(), Buffer::Target::Vertex);
        // ISSUE is here
        // ibo = std::make_unique<Buffer>(indices.size(), indices.data(), Buffer::Target::Index);
        // layout = std::make_unique<VertexLayout>();
        // layout->push<float>(3, false);
        // vao = std::make_unique<VertexArray>(*vbo, *layout);

        return window;
    }

    virtual void render() override
    {
        VertexArray vao{};
        vao.bind();

        vbo->bind();
        GL_CALL(glEnableVertexAttribArray(0));
        GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr));

        GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 3));

        // double dt = timer.delta();

        logger().info("%.2lffps", counter.fps());

        // if (dt > 0.5)
        // {
        //     timer.reset();
        //     points[0].x++;
        //     if (points[0].x > 3)
        //     {
        //         points[0].x = -3;
        //     }
        // }

        // ibo->bind();
        // Renderer::draw_elements(*vao, 3);
        // ibo->unbind();

        // vbo->set_data(0, 3 * sizeof(Vertex), points);
        // Renderer::draw(*vao, 0, 3);
    }

public:
    Application() : ApplicationBase("Pong")
    {
    }
};

int main(int argc, const char *argv[])
{
    Application app;
    app.start(argc, argv);
}
