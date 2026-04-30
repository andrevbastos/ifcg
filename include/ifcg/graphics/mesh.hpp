/**
 * @file mesh.hpp
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief Header file for the Mesh class.
 * @details This file defines the Mesh class, which represents a concrete 2D or 3D 
 *          geometry with vertex and index data.
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <vector>
#include <memory>

#include "ifcg/components/error.hpp"
#include "ifcg/common/meshBase.hpp"
#include "ifcg/shader/shader.hpp"
#include "ifcg/shader/vao.hpp"
#include "ifcg/shader/vbo.hpp"
#include "ifcg/shader/ebo.hpp"

namespace ifcg {
    /**
     * @class Mesh
     * @brief Concrete implementation of MeshBase for rendering geometries.
     * @details This class handles the management of OpenGL buffers (VAO, VBO, EBO)
     *          and provides functionality to draw the geometry using a specific shader.
     */
    class Mesh : public ifcg::MeshBase {
    public:
        /**
         * @brief Construct a new Mesh object.
         * @param vertices Vector of vertices defining the geometry.
         * @param indices Vector of indices for indexed drawing.
         * @param shaderID The ID of the shader program to use for rendering.
         * @param drawMode OpenGL primitive draw mode (default: GL_TRIANGLES).
         */
        Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, GLuint shaderID, GLenum drawMode = GL_TRIANGLES);
        
        /**
         * @brief Copy constructor for Mesh.
         * @param other The mesh to copy from.
         */
        Mesh(const Mesh& other);

        /**
         * @brief Duplicate the current mesh.
         * @return std::shared_ptr<MeshBase> A shared pointer to the new Mesh copy.
         */
        std::shared_ptr<MeshBase> duplicate() const override;

        /**
         * @brief Get the vertices of the mesh.
         * @return std::vector<Vertex> The vector of vertices.
         */
        std::vector<Vertex> getVertices() const;

        /**
         * @brief Get the indices of the mesh.
         * @return std::vector<GLuint> The vector of indices.
         */
        std::vector<GLuint> getIndices() const;

        /**
         * @brief Draw the mesh using its current transformation and shader.
         * @param parentModel The transformation matrix of the parent (default: identity).
         */
        void draw(glm::mat4 parentModel = glm::mat4(1.0f)) override;

        /**
         * @brief Set the OpenGL draw mode.
         * @param mode The primitive mode (e.g., GL_TRIANGLES, GL_LINES).
         */
        void setDrawMode(GLenum mode);

    private:
        /**
         * @brief Initializes the OpenGL buffers (VAO, VBO, EBO).
         */
        void setupMesh();

        /// Internal storage for vertices.
        std::vector<Vertex> _vertices;
        /// Internal storage for indices.
        std::vector<GLuint> _indices;
        
        /// Shader program ID.
        GLuint _shaderID;
        /// OpenGL primitive draw mode.
        GLenum _drawMode;

        /// Vertex Array Object.
        VAO _vao;
        /// Vertex Buffer Object.
        VBO _vbo;
        /// Element Buffer Object.
        EBO _ebo;
    };
};