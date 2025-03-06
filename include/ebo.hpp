#pragma once

#include <glad/glad.h>

class EBO
{
public:
    GLuint _id;
    EBO(GLsizeiptr size, const void* indices);

    void bind();
    void unbind();
    void destroy();
};
