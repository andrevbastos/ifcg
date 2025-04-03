#pragma once

class Vertex2D {
public:
    Vertex2D(float x, float y, float r, float g, float b) : x(x), y(y), r(r), g(g), b(b) {}

    float x, y;
    float r, g, b;
};