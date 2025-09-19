/**
 * @file window.hpp
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief Window component for the IFCG library.
 * @details This file declares the Window class responsible for creating and managing the application window.
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace ifcg {
    class Window
    {
    public:
        /**
         * @brief Create a Window object with given width and height
         * @param w Window width
         * @param h Window height
         */
        Window(unsigned int w, unsigned int h, const char* title = "IFCG Window");
        /**
         * @brief Destroy the Window object.
         */
        ~Window();
        /**
         * @brief Test if the current window should close.
         * @return true if the window should close, false otherwise.
         * @return false if the window should remain open.
         */
        bool shouldClose() const;
        /**
         * @brief Get the underlying GLFWwindow pointer.
         * @return Pointer to the GLFWwindow.
         */
        GLFWwindow* getGLFWwindow() const;
        /**
         * @brief Get the height of the window.
         * @return Height in pixels.
         */
        unsigned int getHeight() const;
        /**
         * @brief Get the width of the window.
         * @return Width in pixels.
         */
        unsigned int getWidth() const;
    private:
        // Pointer to the GLFW window instance.
        GLFWwindow* _window;
        // Window dimensions.
        unsigned int _width;
        unsigned int _height;
    };
}