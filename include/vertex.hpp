#pragma once

class Vertex
{
public:
    Vertex(float x, float y, float z) : x_{x}, y_{y}, z_{z}
    {
    }

private:
    float x_, y_, z_;
};
