/**
 * @file pyramid.hpp
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief Pyramid3D class for representing a 3D pyramid mesh.
 * @copyright Copyright (c) 2025
 */
#pragma once

#include "ifcg/graphics/mesh.hpp"

namespace ifcg
{
    /**
     * @class Pyramid
     * @brief Class representing a 3D pyramid mesh.
     * @details This class provides a predefined pyramid mesh with a square base,
     *          inheriting from the Mesh class defined in ifcg::Mesh.
     */
    class Pyramid : public ifcg::Mesh
    {
    public:
        /**
         * @brief Construct a new Pyramid object
         * @param shaderID Shader program ID used for rendering.
         */
        Pyramid(GLuint shaderID);
    };
}
