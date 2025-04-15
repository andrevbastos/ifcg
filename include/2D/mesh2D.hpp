#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader/vao.hpp"
#include "shader/vbo.hpp"
#include "shader/ebo.hpp"
#include "shader/shader.hpp"

namespace mesh2D
{
    class Mesh2D
    {
    public:
        Mesh2D(std::vector<Vertex2D> vertices, std::vector<GLuint> indices, GLuint shaderID);
        Mesh2D(std::vector<Mesh2D> meshes, GLuint shaderID);

        virtual void draw();
        virtual void transform(glm::mat4 t);
        virtual void translate(float tX, float tY);
        virtual void scale(float sX, float sY);
        virtual void rotate(float angle);

		glm::mat4 model = glm::mat4(1.0f);
		std::vector<glm::mat4> models = { glm::mat4(1.0f) };
    private:
        std::vector<Vertex2D> vertices;
        std::vector<GLuint> indices;
        std::vector<GLuint> sizes;
        GLuint shaderID;
        
        VAO vao;
    };

    Mesh2D::Mesh2D(std::vector<Vertex2D> vertices, std::vector<GLuint> indices, GLuint shaderID)
        : vertices(vertices), indices(indices), shaderID(shaderID)
    {
        this->sizes.push_back(indices.size());

		this->vao = vao;
        vao.bind();

        VBO vbo(vertices);
        EBO ebo(indices);
		
        vao.linkAttrib(vbo, 0, 2, GL_FLOAT, sizeof(Vertex2D), (void*) 0);
        vao.linkAttrib(vbo, 1, 4, GL_FLOAT, sizeof(Vertex2D), (void*) (2 * sizeof(float)));

        vao.unbind();
        vbo.unbind();
        ebo.unbind();
    };

    Mesh2D::Mesh2D(std::vector<Mesh2D> meshes, GLuint shaderID)
        : shaderID(shaderID)
    {
        for (unsigned int i = 0; i < meshes.size(); i++) {
            std::vector<Vertex2D> curretnVertices = meshes[i].vertices;
            std::vector<GLuint> currentIndices = meshes[i].indices;
    
            if (vertices.size() != 0) {
                for (GLuint& index : currentIndices) {
                    index += vertices.size();
                }
            }
    
            this->vertices.insert(this->vertices.end(), curretnVertices.begin(), curretnVertices.end());
            this->indices.insert(this->indices.end(), currentIndices.begin(), currentIndices.end());
            this->sizes.push_back(currentIndices.size());
    
            if (i == 0) {
                this->models[0] = meshes[i].model; 
            } else {
                this->models.insert(this->models.end(), meshes[i].model);
            }
        }
    
        VAO vao;
        this->vao = vao;
        vao.bind();
    
        VBO vbo(vertices);
        EBO ebo(indices);
    
        vao.linkAttrib(vbo, 0, 2, GL_FLOAT, sizeof(Vertex3D), (void*)0);
        vao.linkAttrib(vbo, 1, 4, GL_FLOAT, sizeof(Vertex3D), (void*)(2 * sizeof(float)));
    
        vao.unbind();
        vbo.unbind();
        ebo.unbind();
    };
        
    void Mesh2D::draw() {
        GLuint modelLoc = glGetUniformLocation(shaderID, "model");

        vao.bind();
        GLuint currentOffset = 0;

        for (GLuint i = 0; i < sizes.size(); i++) {
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model * models[i]));
            glDrawElements(
                GL_TRIANGLES,
                sizes[i],
                GL_UNSIGNED_INT,
                (void*)(currentOffset * sizeof(GLuint))
            );
            currentOffset += sizes[i];
        }
        vao.unbind();
    };

	void Mesh2D::transform(glm::mat4 t)
	{
		model *= t;
	};

	void Mesh2D::translate(float tX, float tY)
	{
		model = glm::translate(model, glm::vec3(tX, tY, 0.0f));
	}
	
    void Mesh2D::scale(float x, float y) 
    {
		model = glm::scale(model, glm::vec3(x, y, 1.0f));
    }

	void Mesh2D::rotate(float angle)
	{
		glm::mat4 modelSave = model;
		model = glm::mat4(1.0f);
    	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));		
		
		model = modelSave * rotation * model;
	}
};
