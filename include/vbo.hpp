#ifndef VBO_CLASS_H
#define VBO_CLASS_H

/**
* \author André B.
* \date February 27, 2025
* \version March 24, 2025
* \brief Constructor for VBO class
**/

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

#include "vertex2D.hpp"

class VBO
{
public:
    GLuint _id;
	VBO(const std::vector<Vertex2D>& vertices);

    void bind();
    void unbind();
    void destroy();
};

#endif