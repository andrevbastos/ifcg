#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "vao.hpp"
#include "vbo.hpp"
#include "ebo.hpp"
#include "shader.hpp"
#include "vertex2D.hpp"

class Mesh2D
{
public:
	virtual void draw() = 0;
	virtual void rotate(float angle, glm::vec3 axis) = 0;
	virtual void rotate(GLuint modelIndex, float angle, glm::vec3 axis) = 0;
	virtual void scale(float x, float y, float z) = 0;
	virtual void scale(GLuint modelIndex, float x, float y, float z) = 0;

private:
	std::vector<Vertex2D> vertices;
	std::vector<GLuint> indices;
	GLuint shaderID;
	
	VAO vao;
	Mesh2D(std::vector<Vertex2D> vertices, std::vector<GLuint> indices, GLuint shaderID);
};