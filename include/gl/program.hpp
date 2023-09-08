#pragma once

#include "gl/shader.hpp"
#include "gl/uniform.hpp"

#include <optional>
#include <string>

namespace gl
{
class Program : public Object
{
public:
    Program();
    ~Program();
    Program(Program&& other);
    Program& operator=(Program&& other);

    std::optional<Uniform> uniform(const std::string& name) const;

    bool valid() const;

    Program& attach(const Shader& shader);
    Program& detach(const Shader& shader);
    Program& link();
    Program& use();
};

} // namespace gl
