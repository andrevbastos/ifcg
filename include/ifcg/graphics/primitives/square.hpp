/**
 * @file square.hpp
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief Header file for the Square primitive.
 * @copyright Copyright (c) 2025
 */
#pragma once

#include "ifcg/graphics/mesh.hpp"

namespace ifcg
{
    /**
     * @class Square
     * @brief A 2D square mesh primitive.
     * @details This class provides a predefined 2D square geometry.
     *          It inherits from the Mesh class.
     */
    class Square : public ifcg::Mesh
    {
    public:
        /**
         * @brief Construct a new Square object.
         * @param shaderID Shader program ID to use for rendering.
         */
        Square(GLuint shaderID);
    };
}