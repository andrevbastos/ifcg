#pragma once

class Vertex3D {
public:
    Vertex3D(float x, float y, float z, float r, float g, float b) 
    : x(x), y(y), z(z), r(r), g(g), b(b) {}

    float x, y, z;
    float r, g, b;
};