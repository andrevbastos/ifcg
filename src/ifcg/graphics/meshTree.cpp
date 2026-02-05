#include "ifcg/graphics/meshTree.hpp"

namespace ifcg
{
    MeshTree::MeshTree(const MeshTree& other) {
        this->_model = other._model;
        for (const auto& child : other._children) {
            this->addChild(child->duplicate());
        }
    }

    void MeshTree::addChild(MeshBase* child) {
        if (child) {
            _children.push_back(child);
        }
    }

    MeshBase* MeshTree::duplicate() const {
        return new MeshTree(*this);
    }

    void MeshTree::draw(glm::mat4 parentModel) {
        parentModel *= this->_model;
        for (const auto& child : _children) {
            if (child) {
                child->draw(parentModel);
            }
        }
    }

    ifcg::MeshBase* MeshTree::getChild(std::size_t index) const
    {
        if (index < _children.size())
        {
            return _children[index];
        }
        return nullptr;
    };

};