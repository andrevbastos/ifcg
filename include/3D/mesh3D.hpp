#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader/vao.hpp"
#include "shader/vbo.hpp"
#include "shader/ebo.hpp"
#include "shader/shader.hpp"

namespace mesh3D
{
    class Mesh3D
    {
    public:
        Mesh3D(std::vector<Vertex3D> vertices, std::vector<GLuint> indices, GLuint shaderID);
        
        virtual void draw();
        virtual void transform(glm::mat4 t);
        virtual void translate(float tX, float tY, float tZ);
        virtual void scale(float sX, float sY, float sZ);
        virtual void rotate(float angle, glm::vec3 axis);

		glm::mat4 model = glm::mat4(1.0f);
    private:
        std::vector<Vertex3D> vertices;
        std::vector<GLuint> indices;
        GLuint shaderID;
        
        VAO vao;
    };

    Mesh3D::Mesh3D(std::vector<Vertex3D> vertices, std::vector<GLuint> indices, GLuint shaderID)
        : vertices(vertices), indices(indices), shaderID(shaderID)
    {
		this->vao = vao;
        vao.bind();

        VBO vbo(vertices);
        EBO ebo(indices);
		
        vao.linkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex3D), (void*) 0);
        vao.linkAttrib(vbo, 1, 4, GL_FLOAT, sizeof(Vertex3D), (void*) (3 * sizeof(float)));

        vao.unbind();
        vbo.unbind();
        ebo.unbind();

        if (!glIsEnabled(GL_DEPTH_TEST)) {
            glEnable(GL_DEPTH_TEST);
        }
    }

    void Mesh3D::draw() {
        GLuint modelLoc = glGetUniformLocation(shaderID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    
        vao.bind();
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        vao.unbind();
    }

	void Mesh3D::transform(glm::mat4 t)
	{
		model *= t;
	};

	void Mesh3D::translate(float tX, float tY, float tZ)
	{
		model = glm::translate(model, glm::vec3(tX, tY, 0.0f));
	}
	
    void Mesh3D::scale(float sX, float sY, float sZ) 
    {
		model = glm::scale(model, glm::vec3(sX, sY, sZ));
    }

	void Mesh3D::rotate(float angle, glm::vec3 axis)
	{
		glm::mat4 modelSave = model;
		model = glm::mat4(1.0f);
    	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, axis);		
		
		model = modelSave * rotation * model;
	}
};
