/**
 * @file vertex.hpp
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief Vertex structure for 2D and 3D geometries.
 * @copyright Copyright (c) 2025
 */

#pragma once

/**
 * @class Vertex
 * @brief Vertex structure holding position and color data.
 * @details This structure is used to define vertices of 2D and 3D geometries,
 *          including position (x, y, z) and color (r, g, b, a) attributes.
 *          Default values are provided for z(0.0f), r(1.0f), g(0.0f), b(1.0f) and a(1.0f);
 */
class Vertex {
public:
    /**
     * @brief Construct a new Vertex object
     * @param x X position.
     * @param y Y position.
     * @param z Z position.
     * @param r Red color component.
     * @param g Green color component.
     * @param b Blue color component.
     * @param a Alpha component.
     */
    Vertex(float x, float y, float z = 0.0f, float r = 1.0f, float g = 0.0f, float b = 1.0f, float a = 1.0f) 
        : x(x), y(y), z(z), r(r), g(g), b(b), a(a) {}

    // Position data
    float x, y, z;
    // Color data
    float r, g, b, a;
};