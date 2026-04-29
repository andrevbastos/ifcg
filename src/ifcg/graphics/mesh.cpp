#include "ifcg/graphics/mesh.hpp"

namespace ifcg {
    Mesh::Mesh(const Mesh& other)
        : _vertices(other._vertices), _indices(other._indices), _shaderID(other._shaderID), _drawMode(other._drawMode), _vbo(other._vertices), _ebo(other._indices)
    {
        this->_model = other._model;
        setupMesh();
    };

    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, GLuint shaderID, GLenum drawMode)
        : _vertices(vertices), _indices(indices), _shaderID(shaderID), _drawMode(drawMode), _vbo(_vertices), _ebo(_indices)
    {
        setupMesh();
    };

    std::shared_ptr<MeshBase> Mesh::duplicate() const
    {
        return std::make_shared<Mesh>(*this);
    };

    std::vector<Vertex> Mesh::getVertices() const
    {
        return _vertices;
    };

    std::vector<GLuint> Mesh::getIndices() const
    {
        return _indices;
    };

    void Mesh::draw(glm::mat4 parentModel)
    {
        GLuint modelLoc = glGetUniformLocation(_shaderID, "model");
        parentModel *= _model;

        _vao.bind();
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(parentModel));
        glDrawElements(
            _drawMode,
            _indices.size(),
            GL_UNSIGNED_INT,
            (void*)0
        );

        _vao.unbind();
    };

    void Mesh::setDrawMode(GLenum mode) 
    { 
        _drawMode = mode; 
    };

    void Mesh::setupMesh() 
    {
        _vao.bind();
        _vbo.bind();
        _ebo.bind();

        _vao.linkAttrib(_vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, x));
        _vao.linkAttrib(_vbo, 1, 4, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, r));

        _vao.unbind();
        _vbo.unbind();
        _ebo.unbind();

        GLCheckError();
    };
};