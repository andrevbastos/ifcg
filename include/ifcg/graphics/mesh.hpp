#pragma once

#include <vector>
#include <memory>

#include "ifcg/components/error.hpp"
#include "ifcg/common/meshBase.hpp"
#include "ifcg/shader/shader.hpp"
#include "ifcg/shader/vao.hpp"
#include "ifcg/shader/vbo.hpp"
#include "ifcg/shader/ebo.hpp"

namespace ifcg {
    class Mesh : public ifcg::MeshBase {
    public:
        Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, GLuint shaderID);
        Mesh(const Mesh& other);
        Mesh* duplicate() const override;

        virtual void draw(glm::mat4 parentModel = glm::mat4(1.0f));

    private:
        void setupMesh();

        std::vector<Vertex> _vertices;
        std::vector<GLuint> _indices;
        
        GLuint _shaderID;
        VAO _vao;
        VBO _vbo;
        EBO _ebo;
    };
};