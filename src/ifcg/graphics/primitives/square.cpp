#include "ifcg/graphics/primitives/square.hpp"

namespace ifcg
{
    Square::Square(GLuint shaderID)
        : Mesh({
            Vertex{1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
            Vertex{1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f },
            Vertex{-1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
            Vertex{-1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f }
        },
        {
            0, 1, 3,
            1, 2, 3
        },
        shaderID
    ) {}
};
