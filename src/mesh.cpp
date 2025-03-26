#include "mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, GLuint shaderID)
{
	this->vertices = vertices;
	this->indices = indices;
	this->shaderID = shaderID;

	VAO vao;
	this->vao = vao;
	vao.bind();

	VBO vbo(vertices);
	EBO ebo(indices);

	vao.linkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	vao.linkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));

	vao.unbind();
	vbo.unbind();
	ebo.unbind();
}

void Mesh::draw()
{
	GLuint modelLoc = glGetUniformLocation(shaderID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	vao.bind();
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	vao.unbind();
}

void Mesh::rotate(float angle, glm::vec3 axis)
{
	model = glm::rotate(model, angle, axis);
};