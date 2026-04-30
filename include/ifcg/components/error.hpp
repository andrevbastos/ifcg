/**
 * @file error.hpp
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief OpenGL error checking utilities.
 * @details This file provides a macro and a helper function to check for OpenGL 
 *          errors and print them to the standard error stream with file and line information.
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <glad/glad.h>
#include <iostream>

/**
 * @brief Macro for easy OpenGL error checking.
 * @details Automatically passes the current file name and line number to the error checking function.
 *          Usage: GLCheckError();
 */
#define GLCheckError() glCheckError_(__FILE__, __LINE__)

/**
 * @brief Internal function to check for OpenGL errors.
 * @details Polls OpenGL for errors and prints a descriptive message for each error found.
 * @param file The name of the source file where the check is performed.
 * @param line The line number in the source file where the check is performed.
 * @return GLenum The last error code encountered (or GL_NO_ERROR).
 */
inline GLenum glCheckError_(const char *file, int line) {
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR) {
        std::string error;
        switch (errorCode) {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            default:                               error = "UNKNOWN_ERROR"; break;
        }
        std::cerr << "OpenGL Error: " << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}