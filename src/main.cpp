#include <array>
#include <iostream>
#include <memory>
#include <optional>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/matrix.hpp>

#include "config.hpp"

#include "application.hpp"
#include "cmdline.hpp"
#include "fps_counter.hpp"

#include "gl/buffer.hpp"
#include "gl/program.hpp"
#include "gl/shader.hpp"
#include "gl/vertex_array.hpp"

using namespace gl;

class App : public Application
{
private:
    std::optional<VertexBuffer> vbo;
    std::optional<IndexBuffer> ibo;
    std::optional<VertexArray> vao;

    FpsCounter counter{};
    Timer timer{};

    std::array<Vertex, 4> vertices = {
        Vertex{
            .position = {0, 1, 0},
            .color = {1, 0, 0, 1},
        },
        Vertex{
            .position = {1, -1, 0},
            .color = {0, 1, 0, 1},
        },
        Vertex{
            .position = {-1, -1, 0},
            .color = {0, 0, 1, 1},
        },
        Vertex{
            .position = {-1, -1, 0},
            .color = {1, 0, 1, 1},
        },
    };

    std::array<unsigned int, 3> indices = {
        0,
        1,
        2,
    };

protected:
    virtual Window init() override
    {
        Window window{1000, 400, "Pong"};
        window.make_current();

        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        reload_shaders();

        vbo.emplace(4, BufferUsage::DYNAMIC_DRAW);
        ibo.emplace(6, BufferUsage::DYNAMIC_DRAW);
        vao.emplace();

        vao->buffers(*vbo, *ibo);
        vbo->data(4, vertices.data());
        ibo->data(3, indices.data());

        return window;
    }

    void reload_shaders()
    {
        Shader fs{Shader::Type::FRAGMENT};
        Shader vs{Shader::Type::VERTEX};
        fs.source_path("../shaders/shader.fs").compile();
        vs.source_path("../shaders/shader.vs").compile();

        Program program{};
        program.attach(vs).attach(fs).link().use();
        // .detach(fs).detach(vs);
    }

    virtual void render() override
    {
        glClear(GL_COLOR_BUFFER_BIT);

        logger().info("%.2lffps", counter.fps());

        if (timer.delta() > 1)
        {
            reload_shaders();
            timer.reset();
        }

        vao->draw(3);
    }

public:
    App(int argc, const char* argv[]) : Application(argc, argv)
    {
    }
};

std::array<Option, 2> x = {
    Option{"show-fps", "Show FPS overlay"},
    Option{'V', "version", "Print program version"},
};

int main(int argc, const char* argv[])
{
    assert(x[0].required());
    assert(!x[0].found());

    CmdLine cmdline{argc, argv};
    cmdline.getopt(x);
    cmdline.usage(x, "Program Description");

    assert(x[0].required());
    assert(x[0].found());

    std::cout << std::boolalpha << (bool)x[0] << std::endl;
    // const auto &options = cmdline.options();

    // App app{argc, argv};
    // app.start();
}
