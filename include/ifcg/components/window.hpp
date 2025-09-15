/**
 * @file window.hpp
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief Window component for the IFCG library.
 * @details This file declares the Window class responsible for creating and managing the application window.
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <GLFW/glfw3.h>

class Window
{
public:
    /**
     * @brief Create a Window object with given width and height
     * @param w Window width
     * @param h Window height
     */
    Window(GLuint w, GLuint h, const char* title = "IFCG Window");
    /**
     * @brief Destroy the Window object.
     */
    ~Window();
    /**
     * @brief Test if the current window should close.
     * @return true if the window should close, false otherwise.
     * @return false if the window should remain open.
     */
    bool shouldClose();
private:
    GLFWwindow* _window;
    GLuint _width;
    GLuint _height;
};