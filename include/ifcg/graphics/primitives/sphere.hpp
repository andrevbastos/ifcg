/**
 * @file sphere.hpp
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief Sphere class for representing a 3D sphere mesh.
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <math.h>
#include "ifcg/graphics/mesh.hpp"

namespace ifcg
{
    /**
     * @class Sphere
     * @brief Class representing a 3D sphere mesh.
     * @details This class provides a predefined sphere mesh,
     *          inheriting from the Mesh class defined in ifcg::Mesh.
     */
    class Sphere : public ifcg::Mesh
    {
    public:
        /**
         * @brief Destroy the Sphere object
         */
        ~Sphere() = default;
        /**
         * @brief Construct a new Sphere object
         * @param precision Level of detail for the sphere mesh (number of segments).
         * @param shaderID Shader program ID used for rendering.
         */
        Sphere(int precision, GLuint shaderID);
    private:
        // Generates vertex data for the sphere mesh based on the specified precision.
        // Returns a vector of Vertex objects.
        std::vector<Vertex> vertices(int precision);
        // Generates index data for the sphere mesh based on the specified precision.
        // Returns a vector of GLuint indices.
        std::vector<GLuint> indices(int precision);
    };
};