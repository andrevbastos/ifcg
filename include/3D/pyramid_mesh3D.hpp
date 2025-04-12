#pragma once

#include "3D/mesh3D.hpp"

using namespace mesh3D;

class Pyramid3D : public Mesh3D
{
public:
    Pyramid3D(Shader shaderProgram)
        : Mesh3D({
            Vertex3D{+1.0f, -1.0f, +1.0f, 1.0f, 0.0f, 1.0f, 1.0f},
            Vertex3D{+1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 1.0f},
            Vertex3D{-1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 1.0f},
            Vertex3D{-1.0f, -1.0f, +1.0f, 1.0f, 0.0f, 1.0f, 1.0f},
    
            Vertex3D{-1.0f, -1.0f, +1.0f, 0.0f, 0.0f, 1.0f, 1.0f},
            Vertex3D{+1.0f, -1.0f, +1.0f, 0.0f, 0.0f, 1.0f, 1.0f},
            Vertex3D{0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f},
    
            Vertex3D{+1.0f, -1.0f, +1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
            Vertex3D{+1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
            Vertex3D{0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f},
    
            Vertex3D{+1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f},
            Vertex3D{-1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f},
            Vertex3D{0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
    
            Vertex3D{-1.0f, -1.0f, +1.0f, 0.0f, 1.0f, 0.0f, 1.0f},
            Vertex3D{-1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f},
            Vertex3D{0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f}
        },
        {
            0, 1, 3,
            1, 2, 3,
    
            4, 5, 6,
    
            7, 8, 9,
    
            10, 11, 12,
    
            13, 14, 15
        },
        shaderProgram._id)
    {}
};
