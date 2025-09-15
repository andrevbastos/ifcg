/**
 * @file sphere.hpp
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief Sphere3D class for representing a 3D sphere mesh.
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <math.h>
#include "ifcg/graphics3D/geometry/mesh.hpp"

namespace mesh3D
{
    /**
     * @class Sphere3D
     * @brief Class representing a 3D sphere mesh.
     * @details This class provides a predefined sphere mesh,
     *          inheriting from the Mesh3D class defined in mesh3D::Mesh3D.
     */
    class Sphere3D : public Mesh3D
    {
    public:
        /**
         * @brief Destroy the Sphere3D object
         */
        ~Sphere3D() = default;
        /**
         * @brief Construct a new Sphere3D object
         * @param precision Level of detail for the sphere mesh (number of segments).
         * @param shaderID Shader program ID used for rendering.
         */
        Sphere3D(int precision, GLuint shaderID);
    private:
        // Generates vertex data for the sphere mesh based on the specified precision.
        // Returns a vector of Vertex objects.
        std::vector<Vertex> vertices(int precision);
        // Generates index data for the sphere mesh based on the specified precision.
        // Returns a vector of GLuint indices.
        std::vector<GLuint> indices(int precision);
    };
};