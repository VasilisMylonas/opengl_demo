#include "my_app.hpp"
#include <GL/gl.h>

void my_app::load_data()
{
    vbo.data(vertices.size(), vertices.data(), gl::buffer_usage::static_draw);
    ibo_0.data(indices_0.size(), indices_0.data(), gl::buffer_usage::static_draw);
    ibo_1.data(indices_1.size(), indices_1.data(), gl::buffer_usage::static_draw);
    ibo_2.data(indices_2.size(), indices_2.data(), gl::buffer_usage::static_draw);

    gl::vertex_layout layout;
    layout.push_back(VERTEX_ATTRIBUTE(vertex, position));
    layout.push_back(VERTEX_ATTRIBUTE(vertex, color));
    layout.push_back(VERTEX_ATTRIBUTE(vertex, texture_coords));

    vao_0.buffers(vbo, ibo_0, layout);
    vao_1.buffers(vbo, ibo_1, layout);
    vao_2.buffers(vbo, ibo_2, layout);

    current_texture.load("./res/missing.jpg");
}

void my_app::load_shaders()
{
    gl::shader vs(gl::shader_type::vertex);
    gl::shader fs(gl::shader_type::fragment);

    vs.set_source(read_file("./shaders/shader.vs"));
    vs.compile();

    fs.set_source(read_file("./shaders/shader.fs"));
    fs.compile();

    gl::program program;
    program.attach(vs);
    program.attach(fs);
    program.link();
    program.use();

    current_program = std::move(program);

    load_uniforms();
}

void my_app::init()
{
    load_data();
    load_shaders();
}

bool my_app::should_close()
{
    return close;
}

void my_app::draw_shape(gl::vertex_array& vao)
{
    u_color->set(vertex_color);
    vao.draw_triangles();
}

void my_app::draw_outline(gl::vertex_array& vao)
{
    glDisable(GL_DEPTH_TEST);
    glLineWidth(2.0f);
    u_color->set(glm::vec3(0.0f, 0.0f, 0.0f));
    vao.draw_line_strip();
    glEnable(GL_DEPTH_TEST);
}

void my_app::render()
{
    // Model
    float angle = static_cast<float>(glfwGetTime()) * 50;
    glm::mat4 model =
        glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

    // View
    glm::mat4 view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), // camera position
                                 glm::vec3(0.0f, 0.0f, 0.0f), // target
                                 glm::vec3(0.0f, 1.0f, 0.0f)  // up vector
    );

    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    int windowWidth = viewport[2];
    int windowHeight = viewport[3];

    // Projection
    glm::mat4 projection =
        glm::perspective(glm::radians(45.0f),                      // FOV
                         (float)windowWidth / (float)windowHeight, // Aspect Ratio
                         0.1f,
                         100.0f);

    // MVP
    glm::mat4 mvp = projection * view * model;

    u_mvp->set(mvp);
    u_texture->set(0);

    glClearColor(clear_color.r, clear_color.g, clear_color.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (shape_selected == 0)
    {
        u_use_texture->set(false);
        draw_shape(vao_0);
        draw_outline(vao_0);
    }
    else if (shape_selected == 1)
    {
        u_use_texture->set(false);
        draw_shape(vao_1);
        draw_outline(vao_1);
    }
    else if (shape_selected == 2)
    {
        u_use_texture->set(true);
        glActiveTexture(GL_TEXTURE0);
        current_texture.bind();
        draw_shape(vao_2);
        current_texture.unbind();
    }

    render_gui();
}

void my_app::load_uniforms()
{
    u_color = current_program.uniform("u_color");
    u_mvp = current_program.uniform("u_mvp");
    u_texture = current_program.uniform("u_texture");
    u_use_texture = current_program.uniform("u_use_texture");
}

void my_app::render_gui()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGuiFileDialog::Instance()->Display("LoadImageKey"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();
                current_texture.load(filePath);
            }
            ImGuiFileDialog::Instance()->Close();
        }

        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Load Image"))
            {
                ImGuiFileDialog::Instance()->OpenDialog(
                    "LoadImageKey", "Choose Image", ".jpg,.png,.bmp");
            }

            if (ImGui::MenuItem("Reload Shaders"))
            {
                load_shaders();
            }

            if (ImGui::BeginMenu("Shape"))
            {
                std::array<const char*, 3> shapes = {"Pyramid", "Cube", "Textured Quad"};

                for (int i = 0; i < shapes.size(); ++i)
                {
                    if (ImGui::MenuItem(shapes[i], nullptr, shape_selected == i))
                    {
                        shape_selected = i;
                    }
                }
                ImGui::EndMenu();
            }

            if (ImGui::MenuItem("Exit"))
            {
                close = true;
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    if (ImGui::Begin("Color Selection"))
    {
        ImGui::ColorEdit3("Background Color", glm::value_ptr(clear_color));
        ImGui::ColorEdit3("Foreground Color", glm::value_ptr(vertex_color));
    }
    ImGui::End(); // This needs to be outside `if`
}
