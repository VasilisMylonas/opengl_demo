#pragma once

#include "gl/shader.hpp"

namespace gl
{
class Program : public Object
{
public:
    Program();
    ~Program();
    Program(Program&& other);
    Program& operator=(Program&& other);

    bool valid() const;

    Program& attach(const Shader& shader);
    Program& detach(const Shader& shader);
    Program& link();
    Program& use();
};

} // namespace gl
