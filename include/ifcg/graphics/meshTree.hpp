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

        std::shared_ptr<MeshBase> duplicate() const override;
        void draw(glm::mat4 parentModel = glm::mat4(1.0f)) override;

        void addChild(std::shared_ptr<MeshBase> child);
        std::shared_ptr<MeshBase> getChild(std::size_t index) const;

    private:
        std::vector<std::shared_ptr<MeshBase>> _children;
    };
};