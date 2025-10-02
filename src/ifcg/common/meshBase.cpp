#include "ifcg/common/meshBase.hpp"

namespace ifcg
{
    void MeshBase::translate(float tX, float tY, float tZ)
    {
        _model = glm::translate(_model, glm::vec3(tX, tY, tZ));
    };

    void MeshBase::scale(float sX, float sY, float sZ)
    {
        _model = glm::scale(_model, glm::vec3(sX, sY, sZ));
    };

    void MeshBase::rotate(float angle)
    {
        _model = glm::rotate(_model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
    };

    void MeshBase::rotate(float angle, float rX, float rY, float rZ)
    {
        _model = glm::rotate(_model, angle, glm::vec3(rX, rY, rZ));
    };

    void MeshBase::reflect(bool refX, bool refY, bool refZ)
    {
        if (refX)
            _model = glm::scale(_model, glm::vec3(-1.0f, 1.0f, 1.0f));
        if (refY)
            _model = glm::scale(_model, glm::vec3(1.0f, -1.0f, 1.0f));
        if (refZ)
            _model = glm::scale(_model, glm::vec3(1.0f, 1.0f, -1.0f));
    };
};