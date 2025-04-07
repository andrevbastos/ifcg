#ifndef EBO_CLASS_H
#define EBO_CLASS_H

/**
* \author André B.
* \date February 27, 2025
* \version March 15, 2025
* \brief Constructor for EBO class
**/

#include <vector>
#include <glad/glad.h>

class EBO
{
public:
    GLuint ID;
    EBO(const std::vector<GLuint>& indices);

    void bind();
    void unbind();
    void destroy();
};

#endif