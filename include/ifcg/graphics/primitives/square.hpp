#pragma once

#include "ifcg/graphics/mesh.hpp"

namespace ifcg
{
    class Square : public ifcg::Mesh
    {
    public:
        Square(GLuint shaderID);
    };
}