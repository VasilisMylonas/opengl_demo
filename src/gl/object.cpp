#include "gl/object.hpp"

#include <iostream>

namespace gl
{
void clear_error()
{
    while (glGetError() != GL_NO_ERROR)
        ;
}

void check_error(std::string_view file, int line, std::string_view func)
{
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        std::cerr << "OpenGL error at " << file << ":" << line << " in " << func << "() " << error
                  << std::endl;
    }
}

Object::Object(unsigned int handle)
{
    handle_ = handle;
}

Object::Object(Object&& other)
{
    handle_ = other.handle_;
    other.handle_ = 0;
}

Object& Object::operator=(Object&& other)
{
    handle_ = other.handle_;
    other.handle_ = 0;
    return *this;
}

unsigned int Object::handle() const
{
    return handle_;
}

bool Object::is_vertex_array() const
{
    return glIsVertexArray(handle_);
}

bool Object::is_texture() const
{
    return glIsTexture(handle_);
}

bool Object::is_shader() const
{
    return glIsShader(handle_);
}

bool Object::is_program() const
{
    return glIsProgram(handle_);
}

bool Object::is_buffer() const
{
    return glIsBuffer(handle_);
}

} // namespace gl
