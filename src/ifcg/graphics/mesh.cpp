#include "ifcg/graphics/mesh.hpp"

namespace ifcg {
    Mesh::Mesh(const Mesh& other)
        : _vertices(other._vertices), _indices(other._indices), _shaderID(other._shaderID), _vbo(other._vertices), _ebo(other._indices)
    {
        this->_model = other._model;
        setupMesh();
    }

    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, GLuint shaderID)
        : _vertices(vertices), _indices(indices), _shaderID(shaderID), _vbo(_vertices), _ebo(_indices)
    {
        setupMesh();
    };

    Mesh* Mesh::duplicate() const
    {
        return new Mesh(*this);
    };

    void Mesh::draw(glm::mat4 parentModel)
    {
        GLuint modelLoc = glGetUniformLocation(_shaderID, "model");
        parentModel *= _model;

        _vao.bind();
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(parentModel));
        glDrawElements(
            GL_TRIANGLES,
            _indices.size(),
            GL_UNSIGNED_INT,
            (void*)0
        );

        _vao.unbind();
    };

    void Mesh::setupMesh() 
    {
        _vao.bind();
        _vbo.bind();
        _ebo.bind();

        _vao.linkAttrib(_vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*) 0);
        _vao.linkAttrib(_vbo, 1, 4, GL_FLOAT, sizeof(Vertex), (void*) (3 * sizeof(float)));

        _vao.unbind();
        _vbo.unbind();
        _ebo.unbind();

        GLCheckError();
    };
};