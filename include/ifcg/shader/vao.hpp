/**
 * @file vao.hpp
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief Header file for the VAO (Vertex Array Object) class.
 * @details This file defines the VAO class, which encapsulates the functionality
 *          for creating, binding, unbinding, and destroying an OpenGL Vertex Array Object.
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <glad/glad.h>
#include "ifcg/shader/vbo.hpp"

namespace vao
{
    /**
     * @class VAO
     * @brief Class for managing an OpenGL Vertex Array Object (VAO).
     * @details This class provides methods to create, bind, unbind, and destroy a VAO,
     *          as well as linking vertex attributes from VBOs.
     */
    class VAO
    {
    public:
        // OpenGL ID for the VAO
        GLuint _id;
        /** 
         * @brief Construct a new VAO object.
         */
        VAO();
    
        /** 
         * @brief Link a VBO to the VAO and define its vertex attribute layout.
         * @param vbo The VBO to link.
         * @param layout The layout location in the shader.
         * @param numComponents Number of components per vertex attribute (e.g., 3 for vec3).
         * @param type Data type of each component (e.g., GL_FLOAT).
         * @param stride Byte offset between consecutive vertex attributes.
         * @param offset Offset of the first component of the first vertex attribute in the VBO.
         */
        void linkAttrib(VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
        /**
         * @brief Bind the VAO.
         */
        void bind();
        /**
         * @brief Unbind the VAO.
         */
        void unbind();
        /**
         * @brief Destroy the VAO.
         */
        void destroy();
    };
}

using namespace vao;