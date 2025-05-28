#include "ifcg/graphics3D/geometry/mesh.hpp"

namespace mesh3D
{
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
    };

    Mesh3D::Mesh3D(const std::vector<Mesh3D*>& meshes, GLuint shaderID)
        : shaderID(shaderID)
    {
        this->subMeshes = meshes;

        if (!glIsEnabled(GL_DEPTH_TEST)) {
            glEnable(GL_DEPTH_TEST);
        }
    };
        
    void Mesh3D::draw() {
        GLuint modelLoc = glGetUniformLocation(shaderID, "model");

        if (!subMeshes.empty()) {
            for (Mesh3D* mesh : subMeshes) {
                mesh->draw(model);
            }
        } else {
            vao.bind();
    
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glDrawElements(
                GL_TRIANGLES,
                indices.size(),
                GL_UNSIGNED_INT,
                (void*)0
            );
            vao.unbind();
        }
    };

    void Mesh3D::draw(glm::mat4 m)
    {
        GLuint modelLoc = glGetUniformLocation(shaderID, "model");
        m *= model;

        if (!subMeshes.empty()) {
            for (Mesh3D* mesh : subMeshes) {
                mesh->draw(m);
            }
        } else {
            vao.bind();
    
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(m));
            glDrawElements(
                GL_TRIANGLES,
                indices.size(),
                GL_UNSIGNED_INT,
                (void*)0
            );
            vao.unbind();
        }
    };


	void Mesh3D::transform(glm::mat4 t)
	{
		model *= t;
	};

	void Mesh3D::translate(float tX, float tY, float tZ)
	{
		model = glm::translate(model, glm::vec3(tX, tY, 0.0f));
	};

    void Mesh3D::translate(glm::vec3 axis)
    {
		model = glm::translate(model, axis);
	};
	
    void Mesh3D::scale(float sX, float sY, float sZ) 
    {
		model = glm::scale(model, glm::vec3(sX, sY, sZ));
    };
	
    void Mesh3D::scale(glm::vec3 axis) 
    {
		model = glm::scale(model, axis);
    };

	void Mesh3D::rotate(float angle, float rX, float rY, float rZ)
	{
		glm::mat4 modelSave = model;
		model = glm::mat4(1.0f);
    	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(rX, rY, rZ));		
		
		model = modelSave * rotation * model;
	};

	void Mesh3D::rotate(float angle, glm::vec3 axis)
	{
		glm::mat4 modelSave = model;
		model = glm::mat4(1.0f);
    	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, axis);		
		
		model = modelSave * rotation * model;
	};
};