/**
 * @file mesh.hpp
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief Mesh base class for 3D graphics.
 * @copyright Copyright (c) 2025
 */
#pragma once

#include "ifcg/common/mesh.hpp"

namespace mesh3D
{
    /**
     * @class Mesh3D
     * @brief Base class for 3D meshes.
     * @details This class serves as a base for 3D mesh representations,
     *          providing common functionality and drawing capabilities.
     *          It inherits from the generic Mesh class defined in ifcg::Mesh.
     */
    class Mesh3D : public ifcg::Mesh
    {
    public:
        /**
         * @brief Destroy the Mesh3D object
         */
        ~Mesh3D() = default;
        /**
         * @brief Construct a new Mesh3D object
         * @param vertices Vertex data.
         * @param indices Index data.
         * @param shaderID Shader program ID used for rendering.
         */
        Mesh3D(std::vector<Vertex> vertices, std::vector<GLuint> indices, GLuint shaderID);
        /**
         * @brief Copy constructor.
         * @param other The Mesh3D object to copy.
         */
        Mesh3D(const Mesh3D &other);
        /**
         * @brief Duplicate the current mesh.
         * @return Mesh3D* Pointer to the duplicated mesh.
         */
        Mesh3D* duplicate() const override;

        /**
         * @brief Draw the mesh.
         * @param m Model matrix to apply additionally to the mesh's own model matrix.
         */
        void draw(glm::mat4 m = glm::mat4(1.0f)) override;
        /**
         * @brief Draw the mesh outline.
         */
        void drawOutline();
        /**
         * @brief Enable or disable outline rendering for the mesh.
         * @param outline True to enable outline, false to disable.
         */
        void setOutline(bool outline) override;

        /**
         * @brief Translates over the current model matrix.
         * @param tX X-axis translation.
         * @param tY Y-axis translation.
         * @param tZ Z-axis translation.
         */
        void translate(float tX, float tY, float tZ) override;
        /**
         * @brief Scales over the current model matrix.
         * @param sX X-axis scale factor.
         * @param sY Y-axis scale factor.
         * @param sZ Z-axis scale factor.
         */
        void scale(float sX, float sY, float sZ) override;
        /**
         * @brief Rotates over the current model matrix.
         * @param angle Angle in radians.
         * @param rX X-axis rotation amount over angle.
         * @param rY Y-axis rotation amount over angle.
         * @param rZ Z-axis rotation amount over angle.
         */
        void rotate(float angle, float rX, float rY, float rZ) override;
        /**
         * @brief Reflects the current mesh model over the given axes.
         * @param refX X-axis reflection.
         * @param refY Y-axis reflection.
         * @param refZ Z-axis reflection.
         */
        void reflect(bool refX, bool refY, bool refZ) override;

        // Vertex and index data
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;

        // Model transformation matrix
        glm::mat4 model = glm::mat4(1.0f);

    private:
        // Shader program ID
        GLuint shaderID;
        // Vertex Array Object for rendering
        VAO vao;

        // Outline rendering flag
        bool outline = false;
    };
};

using namespace mesh3D;