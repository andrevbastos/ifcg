#pragma once

/**
* \author André B.
* \date February 27, 2025
* \version March 13, 2025
* \brief Constructor for VAO class
**/

#include <glad/glad.h>
#include "shader/vbo.hpp"

namespace vao
{
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

    VAO::VAO()
    {
        glGenVertexArrays(1, &_id);
    }

    void VAO::linkAttrib(VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
    {
        vbo.bind();
        glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(layout);
    }

    void VAO::bind()
    {
        glBindVertexArray(_id);
    }

    void VAO::unbind()
    {
        glBindVertexArray(0);
    }

    void VAO::destroy()
    {
        glDeleteVertexArrays(1, &_id);
    }
}

using namespace vao;