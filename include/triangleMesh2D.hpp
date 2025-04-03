#pragma once

#include "mesh2D.hpp"

using namespace mesh2D;

class Triangle2D : public Mesh2D
{
public:
    Triangle2D(Shader shaderProgram)
        : Mesh2D({
            Vertex2D{1.0f, -1.0f, 0.0f, 0.0f, 1.0f},
            Vertex2D{-1.0f, -1.0f, 1.0f, 0.0f, 0.0f},
            Vertex2D{0.0f, 1.0f, 0.0f, 1.0f, 0.0f}
        },
        {
            0, 1, 2
        },
        shaderProgram._id)
    {}
};
