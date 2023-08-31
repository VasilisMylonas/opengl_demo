#include <iostream>
#include <cstdlib>
#include <memory>

#include "config.hpp"
#include "shader.hpp"
#include "vertex.hpp"
#include "vertex_buffer.hpp"
#include "vertex_array.hpp"
#include "application_base.hpp"
#include "renderer.hpp"

// std::string load_file(const char *path)
// {
//     FILE *f = fopen(path, "rb");

//     struct stat st;
//     fstat(fileno(f), &st);

//     std::string contents;
//     contents.resize(st.st_size);

//     fread(contents.data(), sizeof(char), st.st_size, f);
//     fclose(f);

//     return contents;
// }

class Application : public ApplicationBase
{
private:
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

    std::unique_ptr<VertexBuffer> vbo;
    std::unique_ptr<VertexArray> vao;

protected:
    virtual void init() override
    {
        vbo = std::make_unique<VertexBuffer>(3 * sizeof(Vertex), points);
        vao = std::make_unique<VertexArray>(*vbo);

        Shader shader(fragment_shader, vertex_shader);
        Renderer::use_shader(shader);
    }

    virtual void render() override
    {
        Renderer::draw(*vao, 0, 3);
    }
};

int main()
{
    Application app;
    app.start();
}
