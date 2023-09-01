#pragma once

class Timer
{
private:
    double t0_;

public:
    Timer() { reset(); }
    double delta() const;
    void reset();
};
