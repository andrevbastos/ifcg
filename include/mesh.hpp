#ifndef MESH_CLASS_h
#define MESH_CLASS_h

#include <string>
#include "vao.hpp"
#include "ebo.hpp"

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	VAO vao;
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);
	void draw();
};

#endif