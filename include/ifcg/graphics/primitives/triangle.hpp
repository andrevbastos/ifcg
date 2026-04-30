/**
 * @file triangle.hpp
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief Header file for the Triangle primitive.
 * @copyright Copyright (c) 2025
 */
#pragma once

#include "ifcg/graphics/mesh.hpp"

namespace ifcg
{
    /**
     * @class Triangle
     * @brief A 2D triangle mesh primitive.
     * @details This class provides a predefined 2D triangle geometry.
     *          It inherits from the Mesh class.
     */
    class Triangle : public ifcg::Mesh
    {
    public:
        /**
         * @brief Construct a new Triangle object.
         * @param shaderID Shader program ID to use for rendering.
         */
        Triangle(GLuint shaderID);
    };
}