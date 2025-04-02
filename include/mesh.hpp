#ifndef MESH_CLASS_h
#define MESH_CLASS_h

/**
* \authors André B.; Helder M.
* \date March 20, 2025
* \version March 28, 2025
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
	std::vector<GLuint> meshSize;
	GLuint shaderID;
	
	std::vector<glm::mat4> models = { glm::mat4(1.0f) };
	glm::mat4 model = glm::mat4(1.0f);
	
	VAO vao;
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, GLuint shaderID);
	Mesh(std::vector<Mesh> meshes, GLuint shaderID);

	void draw();
	void rotate(float angle, glm::vec3 axis);
	void rotate(GLuint modelIndex, float angle, glm::vec3 axis);
	void scale(float x, float y, float z);
	void scale(GLuint modelIndex, float x, float y, float z);
};

#endif