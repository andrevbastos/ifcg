#include "ifcg/graphics/meshTree.hpp"

namespace ifcg
{
    MeshTree::MeshTree(const MeshTree& other) {
        this->_model = other._model;
        for (const auto& child : other._children) {
            this->addChild(std::unique_ptr<MeshBase>(child->duplicate()));
        }
    }

    void MeshTree::addChild(std::unique_ptr<MeshBase> child) {
        if (child) {
            _children.push_back(std::move(child));
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

    ifcg::MeshBase* MeshTree::getChild(int index) const
    {
        if (index >= 0 && index < _children.size())
        {
            return _children[index].get();
        }
        return nullptr;
    };

};