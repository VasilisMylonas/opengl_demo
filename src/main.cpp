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
    std::optional<Buffer> ibo;
    std::optional<VertexArray> vao;
    Layout layout = {
        {0, Attribute::vec4<float>},
    };

    FpsCounter counter{};
    Timer timer{};

    std::array<glm::vec4, 6> points = {
        glm::vec4{0.5, 0.5, 0, 1},
        glm::vec4{0.5, -0.5, 0, 1},
        glm::vec4{-0.5, -0.5, 0, 1},
        glm::vec4{-0.5, 0.5, 0, 1},
    };

    std::array<unsigned int, 6> indices = {
        0,
        1,
        2,
        2,
        3,
        0,
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

        ibo = Buffer::from_array(indices, Buffer::Target::INDEX, Buffer::Usage::STATIC_DRAW);

        return window;
    }

    virtual void render() override
    {
        logger().info("%.2lffps", counter.fps());

        if (timer.delta() > 0.5)
        {
            timer.reset();
        }

        // vbo->data(0, points.size() * sizeof(glm::vec4), points.data());
        vao->draw_elements(DrawMode::TRIANGLES, 6, *ibo);
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
