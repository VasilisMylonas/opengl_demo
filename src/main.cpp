#include <iostream>
#include <cstdlib>
#include <sys/stat.h>

#include "config.hpp"
#include "vertex.hpp"
#include "shader.hpp"
#include "application_base.hpp"

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
    GLuint vbo = 0;
    GLuint vao = 0;

    Point points[3] = {
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

    virtual void init() override
    {
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        Shader shader(fragment_shader, vertex_shader);
        glUseProgram(shader.handle());
    }

    virtual void render() override
    {
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
};

int main()
{
    Application app;
    app.start();

    // glfwSwapInterval(0); Turns off vsync
}
