#ifndef MESH_CLASS_h
#define MESH_CLASS_h

/**
* \authors André B.; Helder M.
* \date March 20, 2025
* \version March 20, 2025
* \brief Constructor for Mesh class
**/

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "vao.hpp"
#include "ebo.hpp"
#include "shader.hpp"

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	GLuint shaderID;

	glm::mat4 model = glm::mat4(1.0f);

	VAO vao;
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, GLuint shaderID);

	void draw();
	void rotate(float angle, glm::vec3 axis);
};

#endif