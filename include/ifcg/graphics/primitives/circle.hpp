/**
 * @file circle.hpp
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief Header file for the Circle primitive.
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <math.h>
#include "ifcg/graphics/mesh.hpp"

namespace ifcg
{
    /**
     * @class Circle
     * @brief A 2D circle mesh primitive.
     * @details This class generates a circle geometry based on a specified precision 
     *          (number of segments). It inherits from the Mesh class.
     */
    class Circle : public ifcg::Mesh
    {
    public:
        /**
         * @brief Construct a new Circle object.
         * @param precision Number of segments used to approximate the circle.
         * @param shaderID Shader program ID to use for rendering.
         */
        Circle(int precision, GLuint shaderID);
    private:
        /**
         * @brief Generates vertex data for the circle.
         * @param precision Number of segments.
         * @return std::vector<Vertex> Vector of vertices.
         */
        std::vector<Vertex> vertices(int precision);

        /**
         * @brief Generates index data for the circle.
         * @param precision Number of segments.
         * @return std::vector<GLuint> Vector of indices.
         */
        std::vector<GLuint> indices(int precision);
    };
}