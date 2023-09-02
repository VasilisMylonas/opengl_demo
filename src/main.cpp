#include <iostream>
#include <memory>
#include <array>

#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>

#include "config.hpp"

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
    std::unique_ptr<VertexArray> vao;
    std::unique_ptr<VertexLayout> layout;

    FpsCounter counter{};
    Timer timer{};

    std::array<glm::vec3, 3> points = {
        glm::vec3{0.0f, 0.5f, 0.0f},
        glm::vec3{0.5f, -0.5f, 0.0f},
        glm::vec3{-0.5f, -0.5f, 0.0f},
    };

    double angle = M_PI / 2;

    glm::mat3x3 r = {
        cos(angle), sin(angle), 0,   //
        -sin(angle), -cos(angle), 0, //
        0, 0, 0,                     //
    };

    std::array<unsigned int, 6>
        indices = {
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
        fs.source(fragment_shader).compile();
        vs.source(vertex_shader).compile();

        Program program{};
        program.attach(fs).attach(vs).link().use().detach(fs).detach(vs);

        vbo = std::make_unique<Buffer>();
        vbo->target(Buffer::Target::Array)
            .usage(Buffer::Usage::DYNAMIC_DRAW)
            .size(points.size() * sizeof(glm::vec3))
            .data(points.data());

        // ibo = std::make_unique<Buffer>(indices.size() * sizeof(unsigned int), indices.data(), Buffer::Target::Index, Buffer::Usage::DYNAMIC_DRAW);
        layout = std::make_unique<VertexLayout>();
        layout->attribute<float>(3, false);

        vao = std::make_unique<VertexArray>();
        vao->buffer(*vbo, *layout);

        return window;
    }

    virtual void render() override
    {
        logger().info("%.2lffps", counter.fps());

        if (timer.delta() > 0.5)
        {
            timer.reset();
            points[0] = points[0] * r;
            points[1] = points[1] * r;
            points[2] = points[2] * r;
        }

        vbo->update(0, points.size() * sizeof(glm::vec3), points.data());
        Renderer::draw_arrays(*vao, 0, 3);
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
