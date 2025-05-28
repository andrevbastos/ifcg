#pragma once

#include "ifcg/common/mesh.hpp"

namespace mesh2D
{
    class Mesh2D : public ifcg::Mesh
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