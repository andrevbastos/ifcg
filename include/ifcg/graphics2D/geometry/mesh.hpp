#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ifcg/shader/vao.hpp"
#include "ifcg/shader/vbo.hpp"
#include "ifcg/shader/ebo.hpp"
#include "ifcg/shader/shader.hpp"

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
};

using namespace mesh2D;