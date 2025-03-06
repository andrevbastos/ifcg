#pragma once

#include <glad/glad.h>

class VBO
{
public:
    GLuint _id;
    VBO(GLsizeiptr size, const void* vertices);

    void bind();
    void unbind();
    void destroy();
};
