#pragma once

#include "ifcg/graphics/mesh.hpp"

namespace ifcg
{
    class Triangle : public ifcg::Mesh
    {
    public:
        Triangle(GLuint shaderID);
    };
}