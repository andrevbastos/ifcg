#pragma once

/**
* \author André B.
* \date February 27, 2025
* \version March 15, 2025
* \brief Constructor for EBO class
**/

#include <vector>
#include <glad/glad.h>

namespace ebo
{
    class EBO
    {
    public:
        GLuint ID;
        EBO(const std::vector<GLuint>& indices);
    
        void bind();
        void unbind();
        void destroy();
    };

    EBO::EBO(const std::vector<GLuint>& indices)
    {
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    }

    void EBO::bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    }

    void EBO::unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void EBO::destroy()
    {
        glDeleteBuffers(1, &ID);
    }
}

using namespace ebo;