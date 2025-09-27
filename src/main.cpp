// #include "main_window.hpp"

// int main(int argc, const char* argv[])
// {
//     vcl::Application app{argc, argv};
//     app.start<MainWindow>();
// }

#include "window.hpp"
#include <cstdio>
#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void glfw_error([[maybe_unused]] int error, const char* description) {
    fprintf(stderr, "GLFW Error: %s\n", description);
}

int main() {
    glfwSetErrorCallback(glfw_error);

    if (glfwInit() == GLFW_FALSE) {
        return EXIT_FAILURE;
    }

    {
        Window window(1200, 800, "OpenGL Demo", 4, 0);
        window.show();

        window.make_current();
        window.swap_interval(1); // Enable vsync

        while (!window.should_close()) {
            glfwPollEvents();

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            window.swap_buffers();
        }
    }

    glfwTerminate();

    return EXIT_SUCCESS;
}
