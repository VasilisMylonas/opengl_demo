#pragma once

#include <GL/glew.h>

#include <cstddef>
#include <string_view>

#define GL_CALL(function)                                                                          \
    gl::clear_error();                                                                             \
    function;                                                                                      \
    gl::check_error(__FILE__, __LINE__, __func__)

namespace gl
{

void clear_error();
void check_error(std::string_view file, int line, std::string_view func);

class Object
{
protected:
    unsigned int handle_;
    Object(unsigned int handle);
    Object(const Object&) = delete;
    Object& operator=(const Object&) = delete;

    // ! WARNING: weird bind behavior
    bool is_vertex_array() const;

    // ! WARNING: weird bind behavior
    bool is_buffer() const;

    // ! WARNING: weird bind behavior
    bool is_texture() const;

    bool is_shader() const;
    bool is_program() const;

public:
    Object(Object&& other);
    Object& operator=(Object&& other);
    unsigned int handle() const;
};

} // namespace gl