#pragma once

#include <glad/glad.h>

#include "vbo.hpp"

class VAO
{
public:
    GLuint _id;
    VAO();

    void linkAttrib(VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
    void bind();
    void unbind();
    void destroy();
};
