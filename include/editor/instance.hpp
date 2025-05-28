#pragma once

#include "3D/mesh3D.hpp"

namespace mesh3D
{
    class Instance
    {
    public:
        Instance(Mesh3D mesh, glm::vec3 center);
    private:
        Mesh3D mesh;
        glm::vec3 center;
    };

    Instance::Instance(Mesh3D mesh, glm::vec3 center)
        : mesh(mesh), center(center)
    {
        this->mesh.translate(center);
    }
}