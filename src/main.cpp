#include <iostream>
#include <memory>
#include <array>
#include <optional>

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
    std::optional<Buffer> vbo;
    std::optional<VertexArray> vao;
    Layout layout = {
        {0, Attribute::vec4<float>},
    };

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
        Window window{1000, 400, "Pong"};
        window.make_current();

        Shader fs{Shader::Type::FRAGMENT};
        Shader vs{Shader::Type::VERTEX};
        fs.source(fragment_shader).compile();
        vs.source(vertex_shader).compile();

        Program program{};
        program.attach(fs).attach(vs).link().use().detach(fs).detach(vs);

        vbo = Buffer::from_array(points, Buffer::Target::ARRAY, Buffer::Usage::DYNAMIC_DRAW);

        vao.emplace();
        vao->buffer(*vbo, layout);

        return window;
    }

    virtual void render() override
    {
        logger().info("%.2lffps", counter.fps());

        if (timer.delta() > 0.5)
        {
            timer.reset();
        }

        vbo->data(0, points.size() * sizeof(glm::vec4), points.data());
        vao->draw(3);
    }

public:
    App(int argc, const char *argv[]) : Application(argc, argv)
    {
    }
};

int main(int argc, const char *argv[])
{
    App app{argc, argv};
    app.start();
}
