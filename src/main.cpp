#include <array>
#include <iostream>
#include <memory>
#include <optional>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/matrix.hpp>

#include "application.hpp"
#include "command_line.hpp"
#include "fps_counter.hpp"

#include "gl/buffer.hpp"
#include "gl/program.hpp"
#include "gl/renderer.hpp"
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
        program.attach(vs).attach(fs).link().use().detach(fs).detach(vs);
    }

public:
    virtual void render() override
    {
        Renderer::clear();

        Application::current().logger().info("%.2lffps", counter.fps());

        if (timer.delta() > 1)
        {
            reload_shaders();
            timer.reset();
        }

        Renderer::draw(vao, 3);
    }

    MainWindow() : Window{1000, 400, "Pong"}
    {
        Renderer::enable_blending();

        reload_shaders();

        vao.buffers(vbo, ibo);
        vbo.data(4, vertices.data());
        ibo.data(3, indices.data());
    }
};

struct
{
    std::optional<bool> show_fps{false};
    std::optional<bool> show_version;
    std::optional<int> lock_fps;
} program_options;

std::array<CommandLine::Option, 3> options = {
    make_option("show-fps", "Show FPS overlay", program_options.show_fps),
    make_option("lock-fps", "Set maximum FPS (default is unlimited)", program_options.lock_fps),
    make_option('V', "version", "Print program version", program_options.show_version),
};

int main(int argc, const char* argv[])
{
    CommandLine cmdline{argc, argv};

    for (auto& option : options)
    {
        cmdline.getopt(option);
    }

    cmdline.usage(options, "Program Description");

    // std::cout << program_options.show_fps.value() << std::endl;
    // std::cout << program_options.lock_fps.value_or(0) << std::endl;

    // Application app{argc, argv};
    // app.start<MainWindow>();
}
