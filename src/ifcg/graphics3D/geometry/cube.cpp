#include "ifcg/graphics3D/geometry/cube.hpp"

namespace mesh3D
{
    Cube3D::Cube3D(GLuint shaderID)
        : Mesh3D({
            Vertex3D{+1.0f, +1.0f, +1.0f, 0.0f, 0.0f, 1.0f, 1.0f},
            Vertex3D{+1.0f, -1.0f, +1.0f, 0.0f, 0.0f, 1.0f, 1.0f},
            Vertex3D{-1.0f, -1.0f, +1.0f, 0.0f, 0.0f, 1.0f, 1.0f},
            Vertex3D{-1.0f, +1.0f, +1.0f, 0.0f, 0.0f, 1.0f, 1.0f},
    
            Vertex3D{+1.0f, +1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f},
            Vertex3D{+1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f},
            Vertex3D{-1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f},
            Vertex3D{-1.0f, +1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f},
    
            Vertex3D{-1.0f, +1.0f, +1.0f, 0.0f, 1.0f, 0.0f, 1.0f},
            Vertex3D{-1.0f, -1.0f, +1.0f, 0.0f, 1.0f, 0.0f, 1.0f},
            Vertex3D{-1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f},
            Vertex3D{-1.0f, +1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f},
    
            Vertex3D{+1.0f, -1.0f, +1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
            Vertex3D{+1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
            Vertex3D{+1.0f, +1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
            Vertex3D{+1.0f, +1.0f, +1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
    
            Vertex3D{+1.0f, +1.0f, +1.0f, 0.0f, 1.0f, 1.0f, 1.0f},
            Vertex3D{+1.0f, +1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f},
            Vertex3D{-1.0f, +1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f},
            Vertex3D{-1.0f, +1.0f, +1.0f, 0.0f, 1.0f, 1.0f, 1.0f},
    
            Vertex3D{+1.0f, -1.0f, +1.0f, 1.0f, 0.0f, 1.0f, 1.0f},
            Vertex3D{+1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 1.0f},
            Vertex3D{-1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 1.0f},
            Vertex3D{-1.0f, -1.0f, +1.0f, 1.0f, 0.0f, 1.0f, 1.0f}
        },
        {
            0, 1, 3,
            1, 2, 3,
    
            4, 5, 7,
            5, 6, 7,
    
            8, 9, 11,
            9, 10, 11,
    
            12, 13, 15,
            13, 14, 15,
    
            16, 17, 19,
            17, 18, 19,
    
            20, 21, 23,
            21, 22, 23
        },
        shaderID
    ) {};
};
