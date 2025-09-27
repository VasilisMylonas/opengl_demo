#include "vcl/timer.hpp"

#include <GLFW/glfw3.h>

namespace vcl
{

Timer::Timer()
{
    reset();
}

double Timer::delta() const
{
    return glfwGetTime() - t0_;
}

void Timer::reset()
{
    t0_ = glfwGetTime();
}

} // namespace vcl
