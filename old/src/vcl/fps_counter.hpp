#pragma once

#include "timer.hpp"

namespace vcl
{

class FpsCounter
{
private:
    unsigned int frame_count_{0};
    double fps_{0};
    Timer timer_{};
    double sample_interval_;

public:
    FpsCounter(double sample_interval = 0.5);
    double sample_interval() const;
    void sample_interval(double value);
    double fps();
};

} // namespace vcl
