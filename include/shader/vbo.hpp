#pragma once

/**
* \author André B.
* \date February 27, 2025
* \version March 24, 2025
* \brief Constructor for VBO class
**/

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

#include "2D/vertex2D.hpp"
#include "3D/vertex3D.hpp"

namespace vbo
{

    class VBO
    {
    public:
        GLuint _id;
        VBO(const std::vector<Vertex2D>& vertices);
        VBO(const std::vector<Vertex3D>& vertices);
    
        void bind();
        void unbind();
        void destroy();
    };
        
    VBO::VBO(const std::vector<Vertex2D>& vertices)
    {
        glGenBuffers(1, &_id);
        glBindBuffer(GL_ARRAY_BUFFER, _id);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex2D), vertices.data(), GL_STATIC_DRAW);
    }
    
    VBO::VBO(const std::vector<Vertex3D>& vertices)
    {
        glGenBuffers(1, &_id);
        glBindBuffer(GL_ARRAY_BUFFER, _id);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex3D), vertices.data(), GL_STATIC_DRAW);
    }
    
    void VBO::bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, _id);
    }
    
    void VBO::unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    
    void VBO::destroy()
    {
        glDeleteBuffers(1, &_id);
    }
}

using namespace vbo;