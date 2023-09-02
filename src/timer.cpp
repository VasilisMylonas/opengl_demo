#include "timer.hpp"

#include <GLFW/glfw3.h>

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