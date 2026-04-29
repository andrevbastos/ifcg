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
        Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, GLuint shaderID, GLenum drawMode = GL_TRIANGLES);
        Mesh(const Mesh& other);
        std::shared_ptr<MeshBase> duplicate() const override;

        std::vector<Vertex> getVertices() const;
        std::vector<GLuint> getIndices() const;

        virtual void draw(glm::mat4 parentModel = glm::mat4(1.0f));
        void setDrawMode(GLenum mode);

    private:
        void setupMesh();

        std::vector<Vertex> _vertices;
        std::vector<GLuint> _indices;
        
        GLuint _shaderID;
        GLenum _drawMode;

        VAO _vao;
        VBO _vbo;
        EBO _ebo;
    };
};