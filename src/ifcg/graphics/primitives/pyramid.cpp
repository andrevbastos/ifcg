#include "ifcg/graphics/primitives/pyramid.hpp"

namespace ifcg
{
    Pyramid::Pyramid(GLuint shaderID)
        : Mesh({
            Vertex{+1.0f, -1.0f, +1.0f, 1.0f, 0.0f, 1.0f, 1.0f},
            Vertex{+1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 1.0f},
            Vertex{-1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 1.0f},
            Vertex{-1.0f, -1.0f, +1.0f, 1.0f, 0.0f, 1.0f, 1.0f},
    
            Vertex{-1.0f, -1.0f, +1.0f, 0.0f, 0.0f, 1.0f, 1.0f},
            Vertex{+1.0f, -1.0f, +1.0f, 0.0f, 0.0f, 1.0f, 1.0f},
            Vertex{0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f},
    
            Vertex{+1.0f, -1.0f, +1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
            Vertex{+1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
            Vertex{0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f},
    
            Vertex{+1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f},
            Vertex{-1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f},
            Vertex{0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
    
            Vertex{-1.0f, -1.0f, +1.0f, 0.0f, 1.0f, 0.0f, 1.0f},
            Vertex{-1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f},
            Vertex{0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f}
        },
        {
            0, 1, 3,
            1, 2, 3,
    
            4, 5, 6,
    
            7, 8, 9,
    
            10, 11, 12,
    
            13, 14, 15
        },
        shaderID
    ) {}
}
