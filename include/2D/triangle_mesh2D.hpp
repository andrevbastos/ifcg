#pragma once

#include "2D/mesh2D.hpp"

using namespace mesh2D;

class Triangle2D : public Mesh2D
{
public:
    Triangle2D(GLuint shaderID)
        : Mesh2D(
        {
            Vertex2D{  1.0f, -0.866f, 1.0f, 0.0f, 0.0f, 1.0f },
            Vertex2D{ -1.0f, -0.866f, 0.0f, 1.0f, 0.0f, 1.0f },
            Vertex2D{  0.0f,  0.866f, 0.0f, 0.0f, 1.0f, 1.0f }
        },
        {
            0, 1, 2
        },
        shaderID
    ) {}
};
