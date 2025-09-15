/**
 * @file ebo.hpp
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief Header file for the EBO (Element Buffer Object) class.
 * @details This file defines the EBO class, which encapsulates the functionality
 *          for creating, binding, unbinding, and destroying an OpenGL Element Buffer Object.
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <vector>
#include <glad/glad.h>

namespace ebo
{
    /**
     * @class EBO
     * @brief Class for managing an OpenGL Element Buffer Object (EBO).
     * @details This class provides methods to create, bind, unbind, and destroy an EBO.
     */
    class EBO
    {
    public:
        // OpenGL ID for the EBO
        GLuint ID;
        /**
         * @brief Construct a new EBO object.
         * @param indices A vector of unsigned integers representing the indices.
         */
        EBO(const std::vector<GLuint>& indices);

        /**
         * @brief Bind the EBO.
         */
        void bind();
        /**
         * @brief Unbind the EBO.
         */
        void unbind();
        /**
         * @brief Destroy the EBO.
         */
        void destroy();
    };
}

using namespace ebo;