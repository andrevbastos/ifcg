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
 *          Default values are provided for z(0.0f), r(1.0f), g(0.0f), b(1.0f), a(1.0f), u(0.0f), v(0.0f).
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
    Vertex(float x, float y, float z = 0.0f, 
           float r = 1.0f, float g = 0.0f, float b = 1.0f, float a = 1.0f)
        : x(x), y(y), z(z), r(r), g(g), b(b), a(a) {}

    /// X position coordinate.
    float x;
    /// Y position coordinate.
    float y;
    /// Z position coordinate.
    float z;
    
    /// Red color component (0.0f to 1.0f).
    float r;
    /// Green color component (0.0f to 1.0f).
    float g;
    /// Blue color component (0.0f to 1.0f).
    float b;
    /// Alpha transparency component (0.0f to 1.0f).
    float a;

    // Operator overloads for vertex arithmetic with clamping for color components.
    Vertex operator+(const Vertex& other) const {
        return Vertex(
            x + other.x,
            y + other.y,
            z + other.z,
            r + other.r > 1.0f ? 1.0f : r + other.r, 
            g + other.g > 1.0f ? 1.0f : g + other.g, 
            b + other.b > 1.0f ? 1.0f : b + other.b, 
            a + other.a > 1.0f ? 1.0f : a + other.a
        );
    }

    // Operator overload for vertex subtraction with clamping for color components.
    Vertex operator-(const Vertex& other) const {
        return Vertex(
            x - other.x,
            y - other.y,
            z - other.z,
            r - other.r < 0.0f ? 0.0f : r - other.r, 
            g - other.g < 0.0f ? 0.0f : g - other.g, 
            b - other.b < 0.0f ? 0.0f : b - other.b, 
            a - other.a < 0.0f ? 0.0f : a - other.a
        );
    }

    /**
     * @brief Operator overload for vertex interpolation.
     * @param other The other vertex to interpolate with.
     * @return The interpolated vertex.
     */
    Vertex operator%(const Vertex& other) const {
        return Vertex(
            (x + other.x) * 0.5f,
            (y + other.y) * 0.5f,
            (z + other.z) * 0.5f,
            (r + other.r) * 0.5f,
            (g + other.g) * 0.5f,
            (b + other.b) * 0.5f,
            (a + other.a) * 0.5f
        );
    }
};