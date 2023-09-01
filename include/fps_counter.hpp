#pragma once

#include "config.hpp"
#include "timer.hpp"

class FpsCounter
{
private:
    unsigned int frame_count_{0};
    double fps_{0};
    Timer timer_{};

public:
    double fps()
    {
        double dt = timer_.delta();

        if (dt > FPS_SAMPLE_INTERVAL)
        {
            fps_ = frame_count_ / dt;
            frame_count_ = 0;
            timer_.reset();
        }

        frame_count_++;

        return fps_;
    }
};
