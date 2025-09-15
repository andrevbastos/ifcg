/**
 * @file cube.hpp
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief Cube mesh for 3D graphics.
 * @copyright Copyright (c) 2025
 */
#pragma once

#include "ifcg/graphics3D/geometry/mesh.hpp"

namespace mesh3D
{
    /**
     * @class Cube3D
     * @brief Cube mesh for 3D graphics.
     * @details This class represents a 3D cube mesh, inheriting from Mesh3D.
     *          It initializes a simple cube's vertices and indices, and provides
     *          functionality to manipulate and render the cube in a 3D space.
     */
    class Cube3D : public Mesh3D
    {
    public:
        Cube3D(GLuint shaderID);
    };
}
