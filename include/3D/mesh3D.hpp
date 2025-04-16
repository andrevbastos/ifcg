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
	    Mesh3D(std::vector<Mesh3D> meshes, GLuint shaderID);

        virtual void draw();
        virtual void transform(glm::mat4 t);
        virtual void translate(float tX, float tY, float tZ);
        virtual void scale(float sX, float sY, float sZ);
        virtual void rotate(float angle, glm::vec3 axis);

		glm::mat4 model = glm::mat4(1.0f);
		std::vector<glm::mat4> models = { glm::mat4(1.0f) };
    private:
        std::vector<Vertex3D> vertices;
        std::vector<GLuint> indices;
        std::vector<GLuint> sizes;
        GLuint shaderID;
        
        VAO vao;
    };

    Mesh3D::Mesh3D(std::vector<Vertex3D> vertices, std::vector<GLuint> indices, GLuint shaderID)
        : vertices(vertices), indices(indices), shaderID(shaderID)
    {
        this->sizes.push_back(indices.size());

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
    };

    Mesh3D::Mesh3D(std::vector<Mesh3D> meshes, GLuint shaderID)
        : shaderID(shaderID)
    {
        for (unsigned int i = 0; i < meshes.size(); i++) {
            std::vector<Vertex3D> curretnVertices = meshes[i].vertices;
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
    
        vao.linkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex3D), (void*)0);
        vao.linkAttrib(vbo, 1, 4, GL_FLOAT, sizeof(Vertex3D), (void*)(3 * sizeof(float)));
    
        vao.unbind();
        vbo.unbind();
        ebo.unbind();

        if (!glIsEnabled(GL_DEPTH_TEST)) {
            glEnable(GL_DEPTH_TEST);
        }
    };
        
    void Mesh3D::draw() {
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

	void Mesh3D::transform(glm::mat4 t)
	{
		model *= t;
	};

	void Mesh3D::translate(float tX, float tY, float tZ)
	{
		model = glm::translate(model, glm::vec3(tX, tY, 0.0f));
	};
	
    void Mesh3D::scale(float sX, float sY, float sZ) 
    {
		model = glm::scale(model, glm::vec3(sX, sY, sZ));
    };

	void Mesh3D::rotate(float angle, glm::vec3 axis)
	{
		glm::mat4 modelSave = model;
		model = glm::mat4(1.0f);
    	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, axis);		
		
		model = modelSave * rotation * model;
	};
};
