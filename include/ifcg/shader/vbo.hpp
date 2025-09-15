/**
 * @file vbo.hpp
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief Header file for the VBO (Vertex Buffer Object) class.
 * @details This file defines the VBO class, which encapsulates the functionality
 *          for creating, binding, unbinding, and destroying an OpenGL Vertex Buffer Object.
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

#include "ifcg/common/vertex.hpp"

namespace vbo
{
    /**
     * @class VBO
     * @brief Class for managing an OpenGL Vertex Buffer Object (VBO).
     * @details This class provides methods to create, bind, unbind, and destroy a VBO.
     */
    class VBO
    {
    public:
        // OpenGL ID for the VBO
        GLuint _id;
        /** 
         * @brief Construct a new VBO object.
         * @param vertices A vector of Vertex structures.
         */
        VBO(const std::vector<Vertex>& vertices);
    
        /** 
         * @brief Bind the VBO.
         */
        void bind();
        /**
         * @brief Unbind the VBO.
         */
        void unbind();
        /**
         * @brief Destroy the VBO.
         */
        void destroy();
    };
}

using namespace vbo;