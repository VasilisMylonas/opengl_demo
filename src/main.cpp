#include <iostream>
#include <memory>
#include <array>

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "config.hpp"

#include "application.hpp"
#include "fps_counter.hpp"
#include "renderer.hpp"

#include "gl/layout.hpp"
#include "gl/shader.hpp"
#include "gl/program.hpp"
#include "gl/buffer.hpp"
#include "gl/vertex_array.hpp"

using namespace gl;

class App : public Application
{
private:
    std::unique_ptr<Buffer> vbo;
    std::unique_ptr<VertexArray> vao;
    std::unique_ptr<Layout> layout;

    FpsCounter counter{};
    Timer timer{};

    std::array<glm::vec4, 3> points = {
        glm::vec4{0.0f, 0.5f, 0.0f, 1.0f},
        glm::vec4{0.5f, -0.5f, 0.0f, 1.0f},
        glm::vec4{-0.5f, -0.5f, 0.0f, 1.0f},
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
        vbo->target(Buffer::Target::ARRAY)
            .usage(Buffer::Usage::DYNAMIC_DRAW)
            .size(points.size() * sizeof(glm::vec4))
            .data(points.data());

        layout = std::make_unique<Layout>();
        layout->push<4, float>();

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
        }

        vbo->update(0, points.size() * sizeof(glm::vec4), points.data());
        vao->draw(3);
    }

public:
    App() : Application("Pong")
    {
    }
};

int main(int argc, const char *argv[])
{
    App app;
    app.start(argc, argv);
}
