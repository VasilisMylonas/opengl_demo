#include "vcl/fps_counter.hpp"

namespace vcl
{

FpsCounter::FpsCounter(double sample_interval) : sample_interval_{sample_interval}
{
}

double FpsCounter::sample_interval() const
{
    return sample_interval_;
}

void FpsCounter::sample_interval(double value)
{
    sample_interval_ = value;
}

double FpsCounter::fps()
{
    double dt = timer_.delta();

    if (dt > sample_interval_)
    {
        fps_ = frame_count_ / dt;
        frame_count_ = 0;
        timer_.reset();
    }

    frame_count_++;

    return fps_;
}

} // namespace vcl
