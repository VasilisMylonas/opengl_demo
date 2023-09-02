#pragma once

class Timer
{
private:
    double t0_;

public:
    Timer();
    double delta() const;
    void reset();
};
