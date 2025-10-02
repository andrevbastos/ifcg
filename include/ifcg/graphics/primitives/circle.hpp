#pragma once

#include <math.h>
#include "ifcg/graphics/mesh.hpp"

namespace ifcg
{
    class Circle : public ifcg::Mesh
    {
    public:
        Circle(int precision, GLuint shaderID);
    private:
        std::vector<Vertex> vertices(int precision);
        std::vector<GLuint> indices(int precision);
    };
}