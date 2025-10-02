#include "ifcg/graphics/primitives/triangle.hpp"

namespace ifcg
{
    Triangle::Triangle(GLuint shaderID)
        : Mesh(
        {
            Vertex{  1.0f, -0.866f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f },
            Vertex{ -1.0f, -0.866f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f },
            Vertex{  0.0f,  0.866f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f }
        },
        {
            0, 1, 2
        },
        shaderID
    ) {}
};
