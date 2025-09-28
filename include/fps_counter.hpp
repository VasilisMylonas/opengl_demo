#pragma once

#include <GLFW/glfw3.h>

namespace vcl
{

class FpsCounter
{
private:
    int frame_count_ = 0;
    double fps_ = 0;
    double t0_;

public:
    FpsCounter()
    {
        t0_ = glfwGetTime();
    }

    double fps()
    {
        double dt = glfwGetTime() - t0_;

        if (dt > 0.5)
        {
            fps_ = frame_count_ / dt;
            frame_count_ = 0;
            t0_ = glfwGetTime();
        }

        frame_count_++;

        return fps_;
    }
};

} // namespace vcl
