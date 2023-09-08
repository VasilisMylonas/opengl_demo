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
#include "gl/uniform.hpp"
#include "gl/vertex_array.hpp"

using namespace gl;

class MainWindow : public Window
{
private:
    VertexBuffer vbo{4, BufferUsage::DYNAMIC_DRAW};
    IndexBuffer ibo{6, BufferUsage::DYNAMIC_DRAW};
    VertexArray vao{};

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

public:
    virtual void render() override
    {
        glClear(GL_COLOR_BUFFER_BIT);

        Application::current().logger().info("%.2lffps", counter.fps());

        if (timer.delta() > 1)
        {
            reload_shaders();
            timer.reset();
        }

        vao.draw(3);
    }

    MainWindow() : Window{1000, 400, "Pong"}
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        reload_shaders();

        vao.buffers(vbo, ibo);
        vbo.data(4, vertices.data());
        ibo.data(3, indices.data());
    }
};

std::array<Option, 3> options = {
    Option{"show-fps", "Show FPS overlay", false},
    Option{"lock-fps", "Set maximum FPS (default is unlimited)", true},
    Option{'V', "version", "Print program version", false},
};

int main(int argc, const char* argv[])
{
    CmdLine cmdline{argc, argv};

    for (Option& option : options)
    {
        if (cmdline.getopt(option))
        {
            // TODO
        }
    }

    cmdline.usage(options, "Program Description");

    Application app{argc, argv};
    app.start<MainWindow>();
}
