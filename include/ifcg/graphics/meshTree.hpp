#pragma once

#include <vector>
#include <memory>
#include "ifcg/common/meshBase.hpp"

namespace ifcg
{
    class MeshTree : public ifcg::MeshBase
    {
    public:
        MeshTree() = default;
        MeshTree(const MeshTree &other); 

        MeshBase* duplicate() const override;
        void draw(glm::mat4 parentModel = glm::mat4(1.0f)) override;

        void addChild(std::unique_ptr<MeshBase> child);
        MeshBase* getChild(int index) const;

    private:
        std::vector<std::unique_ptr<MeshBase>> _children;
    };
};