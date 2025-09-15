/**
 * @file pyramid.hpp
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief Pyramid3D class for representing a 3D pyramid mesh.
 * @copyright Copyright (c) 2025
 */
#pragma once

#include "ifcg/graphics3D/geometry/mesh.hpp"

namespace mesh3D
{
    /**
     * @class Pyramid3D
     * @brief Class representing a 3D pyramid mesh.
     * @details This class provides a predefined pyramid mesh with a square base,
     *          inheriting from the Mesh3D class defined in mesh3D::Mesh3D.
     */
    class Pyramid3D : public Mesh3D
    {
    public:
        /**
         * @brief Destroy the Pyramid3D object
         */
        ~Pyramid3D() = default;
        /**
         * @brief Construct a new Pyramid3D object
         * @param shaderID Shader program ID used for rendering.
         */
        Pyramid3D(GLuint shaderID);
    };
}
