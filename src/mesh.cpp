#include "mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, GLuint shaderID)
{
	this->vertices = vertices;
	this->indices = indices;
	this->shaderID = shaderID;
	this->meshSize.push_back(vertices.size());

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

Mesh::Mesh(std::vector<Mesh> meshes, GLuint shaderID)
{
    for (unsigned int i = 0; i < meshes.size(); i++) {
		std::vector<Vertex> curretnVertices = meshes[i].vertices;
		std::vector<GLuint> currentIndices = meshes[i].indices;
		std::vector<glm::mat4> currentModels = meshes[i].models;

		if (vertices.size() != 0) {
			for (GLuint& index : currentIndices) {
				index += vertices.size();
			}
		}

        this->vertices.insert(this->vertices.end(), curretnVertices.begin(), curretnVertices.end());
		this->indices.insert(this->indices.end(), currentIndices.begin(), currentIndices.end());
		this->meshSize.push_back(currentIndices.size());

		if (i == 0) {
            this->models = currentModels; 
		} else {
            this->models.insert(this->models.end(), currentModels.begin(), currentModels.end());
        }

		std::cout << "MESH VERTICES: " << vertices.size() << std::endl;
		std::cout << "MESH INDICES: "<< indices.size() << std::endl;
		std::cout << "CURRENT MESH INDEX SIZE: " << meshSize[i] << std::endl;
    }
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
};

void Mesh::draw() {
    GLuint modelLoc = glGetUniformLocation(shaderID, "model");

    vao.bind();
    GLuint currentOffset = 0;

    for (GLuint i = 0; i < meshSize.size(); i++) {
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(models[i]));
        glDrawElements(
            GL_TRIANGLES,
            meshSize[i],
            GL_UNSIGNED_INT,
            (void*)(currentOffset * sizeof(GLuint))
        );
        currentOffset += meshSize[i];
    }
    vao.unbind();
}

void Mesh::rotate(float angle, glm::vec3 axis)
{
	for (size_t modelIndex = 0; modelIndex < models.size(); modelIndex++) {
		models[modelIndex] = glm::rotate(models[modelIndex], angle, axis);
	}
};

void Mesh::rotate(GLuint modelIndex, float angle, glm::vec3 axis)
{
	models[modelIndex] = glm::rotate(models[modelIndex], angle, axis);
};

void Mesh::scale(float x, float y, float z) 
{
	for (size_t modelIndex = 0; modelIndex < models.size(); modelIndex++) {
		models[modelIndex] = glm::scale(models[modelIndex], glm::vec3(x,y,z));
	}
};

void Mesh::scale(GLuint modelIndex, float x, float y, float z) 
{
	models[modelIndex] = glm::scale(models[modelIndex], glm::vec3(x,y,z));
};