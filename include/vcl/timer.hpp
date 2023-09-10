#pragma once

namespace vcl
{

class Timer
{
private:
    double t0_;

public:
    Timer();
    double delta() const;
    void reset();
};

} // namespace vcl
