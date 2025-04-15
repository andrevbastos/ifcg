#pragma once

#include "2D/mesh2D.hpp"

using namespace mesh2D;

class Square2D : public Mesh2D
{
public:
    Square2D(GLuint shaderID)
        : Mesh2D({
            Vertex2D{1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f },
            Vertex2D{1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f },
            Vertex2D{-1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f },
            Vertex2D{-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f }
        },
        {
            0, 1, 3,
            1, 2, 3
        },
        shaderID
    ) {}
};
