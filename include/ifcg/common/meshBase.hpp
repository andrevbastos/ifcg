/**
 * @file mesh.hpp
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief Mesh interface for 2D and 3D geometries.
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ifcg
{
    /**
     * @class Mesh
     * @brief Abstract base class for mesh implementations in 2D and 3D geometries.
     * @details This class defines the interface for mesh operations such as drawing,
     *          transformations, and duplication. It also holds vertex and index data
     *          as well as the model transformation matrix.
     */
    class MeshBase
    {
    public:
        /**
         * @brief Destroy the Mesh object
         */
        virtual ~MeshBase() = default;
        /**
         * @brief Duplicate the current mesh.
         * @return MeshBase* 
         */
        virtual MeshBase* duplicate() const = 0;

        /**
         * @brief Draw the mesh.
         * @param m Model matrix to apply aditionally to the mesh's own model matrix.
         */
        virtual void draw(glm::mat4 parentModel = glm::mat4(1.0f)) = 0;

        /**
         * @brief Translates over the current model matrix.
         * @param tX X-axis translation.
         * @param tY Y-axis translation.
         * @param tZ Z-axis translation. Default is 0.0f.
         */
        void translate(float tX, float tY, float tZ = 0.0f);
        /**
         * @brief Scales ove the current model matrix.
         * @param sX X-axis scale factor.
         * @param sY Y-axis scale factor.
         * @param sZ Z-axis scale factor. (Default is 1.0f).
         */
        void scale(float sX, float sY, float sZ = 1.0f);

        /**
         * @brief Rotates over the current model matrix.
         * @param angle Angle in radians.
         */
        void rotate(float angle);
        /**
         * @brief Rotates over the current model matrix.
         * @param angle Angle in radians.
         * @param rX X-axis rotation amount over angle.
         * @param rY Y-axis rotation amount over angle.
         * @param rZ Z-axis rotation amount over angle.
         */
        void rotate(float angle, float rX, float rY, float rZ);
        /**
         * @brief Reflects the current mesh model over the given axes.
         * @param refX X-axis reflection.
         * @param refY Y-axis reflection.
         * @param refZ Z-axis reflection.
         */
        void reflect(bool refX, bool refY, bool refZ = false);

    protected:
        /**
         * @brief Model transformation matrix.
         * @details This matrix hold the cumulative transformations applied to the mesh.
         * It is initialized to the identity matrix.
         */
        glm::mat4 _model = glm::mat4(1.0f);
    };
}