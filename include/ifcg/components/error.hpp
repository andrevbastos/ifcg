#pragma once

#include <glad/glad.h>
#include <iostream>

#define GLCheckError() glCheckError_(__FILE__, __LINE__)
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