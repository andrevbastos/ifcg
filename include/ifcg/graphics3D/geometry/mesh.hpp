#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ifcg/shader/vbo.hpp"
#include "ifcg/shader/vao.hpp"
#include "ifcg/shader/ebo.hpp"
#include "ifcg/shader/shader.hpp"

namespace mesh3D
{
    class Mesh3D
    {
    public:
        Mesh3D(std::vector<Vertex3D> vertices, std::vector<GLuint> indices, GLuint shaderID);
	    Mesh3D(const std::vector<Mesh3D*>& meshes, GLuint shaderID);

        virtual void draw();
        virtual void draw(glm::mat4 m);
        
        virtual void transform(glm::mat4 t);
        virtual void translate(float tX, float tY, float tZ);
        virtual void translate(glm::vec3 axis);
        virtual void scale(float sX, float sY, float sZ);
        virtual void scale(glm::vec3 axis);
        virtual void rotate(float angle, float rX, float rY, float rZ);
        virtual void rotate(float angle, glm::vec3 axis);


    private:
        std::vector<Vertex3D> vertices;
        std::vector<GLuint> indices;

        GLuint shaderID;
        VAO vao;
        
		glm::mat4 model = glm::mat4(1.0f);
		std::vector<Mesh3D*> subMeshes;
    };
};

using namespace mesh3D;