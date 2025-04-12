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
        
        virtual void draw();
        virtual void transform(glm::mat4 t);
        virtual void translate(float tX, float tY);
        virtual void scale(float sX, float sY);
        virtual void rotate(float angle);

		glm::mat4 model = glm::mat4(1.0f);
    private:
        std::vector<Vertex2D> vertices;
        std::vector<GLuint> indices;
        GLuint shaderID;
        
        VAO vao;
    };

    Mesh2D::Mesh2D(std::vector<Vertex2D> vertices, std::vector<GLuint> indices, GLuint shaderID)
        : vertices(vertices), indices(indices), shaderID(shaderID)
    {
		this->vao = vao;
        vao.bind();

        VBO vbo(vertices);
        EBO ebo(indices);
		
        vao.linkAttrib(vbo, 0, 2, GL_FLOAT, sizeof(Vertex2D), (void*) 0);
        vao.linkAttrib(vbo, 1, 4, GL_FLOAT, sizeof(Vertex2D), (void*) (2 * sizeof(float)));

        vao.unbind();
        vbo.unbind();
        ebo.unbind();
    }

    void Mesh2D::draw() {
        GLuint modelLoc = glGetUniformLocation(shaderID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    
        vao.bind();
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        vao.unbind();
    }

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
