#include <iostream>
#include <cstdlib>
#include <memory>

#include "config.hpp"
#include "shader.hpp"
#include "vertex.hpp"
#include "vertex_buffer.hpp"
#include "vertex_array.hpp"
#include "application_base.hpp"
#include "fps_counter.hpp"
#include "renderer.hpp"

class Application : public ApplicationBase
{
private:
    std::unique_ptr<VertexBuffer> vbo;
    std::unique_ptr<IndexBuffer> ibo;
    std::unique_ptr<VertexArray> vao;
    int frame_count = 0;
    FpsCounter counter{};
    Timer timer{};

    Vertex points[3] = {
        {
            0.0f,
            0.5f,
            0.0f,
        },
        {
            0.5f,
            -0.5f,
            0.0f,
        },
        {
            -0.5f,
            -0.5f,
            0.0f,
        },
    };

protected:
    virtual Window init() override
    {
        Window window{1000, 400, name().c_str()};
        window.make_current();

        Shader shader{fragment_shader, vertex_shader};
        Renderer::use_shader(shader);

        unsigned indices[] = {
            0,
            1,
            1,
            2,
            2,
            0,
        };

        vbo = std::make_unique<VertexBuffer>(3, points);
        ibo = std::make_unique<IndexBuffer>(6, indices);
        vao = std::make_unique<VertexArray>(*vbo, *ibo);

        return window;
    }

    virtual void render() override
    {
        double dt = timer.delta();

        logger().info("%.2lffps", counter.fps());

        if (dt > 0.5)
        {
            timer.reset();
            points[0].x_++;
            if (points[0].x_ > 3)
            {
                points[0].x_ = -3;
            }
        }

        vbo->update_data(0, 3, points);
        Renderer::draw(*vao, 6);
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
