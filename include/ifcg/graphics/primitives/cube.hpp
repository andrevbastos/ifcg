/**
 * @file cube.hpp
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief Cube mesh for 3D graphics.
 * @copyright Copyright (c) 2025
 */
#pragma once

#include "ifcg/graphics/mesh.hpp"

namespace ifcg
{
    /**
     * @class Cube
     * @brief Cube mesh for 3D graphics.
     * @details This class represents a 3D cube mesh, inheriting from Mesh.
     *          It initializes a simple cube's vertices and indices, and provides
     *          functionality to manipulate and render the cube in a 3D space.
     */
    class Cube : public ifcg::Mesh
    {
    public:
        Cube(GLuint shaderID);
    };
}
