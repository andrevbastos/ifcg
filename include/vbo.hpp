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

struct Vertex
{
    glm::vec3 position;
	glm::vec3 color;
};

class VBO
{
public:
    GLuint _id;
	VBO(const std::vector<Vertex>& vertices);

    void bind();
    void unbind();
    void destroy();
};

#endif