/**
 * @file meshTree.hpp
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief Header file for the MeshTree class.
 * @details This file defines the MeshTree class, which allows for grouping multiple 
 *          meshes into a hierarchical tree structure for collective transformations.
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <vector>
#include <memory>
#include "ifcg/common/meshBase.hpp"

namespace ifcg
{
    /**
     * @class MeshTree
     * @brief A hierarchical container for MeshBase objects.
     * @details MeshTree allows organizing meshes in a parent-child relationship. 
     *          Transformations applied to the MeshTree are propagated to all its children 
     *          during the draw call.
     */
    class MeshTree : public ifcg::MeshBase
    {
    public:
        /**
         * @brief Default constructor for MeshTree.
         */
        MeshTree() = default;

        /**
         * @brief Copy constructor for MeshTree.
         * @param other The MeshTree to copy from.
         */
        MeshTree(const MeshTree &other); 

        /**
         * @brief Duplicate the current mesh tree and all its children.
         * @return std::shared_ptr<MeshBase> A shared pointer to the new MeshTree copy.
         */
        std::shared_ptr<MeshBase> duplicate() const override;

        /**
         * @brief Draw the mesh tree and all its children.
         * @param parentModel The transformation matrix of the parent (default: identity).
         */
        void draw(glm::mat4 parentModel = glm::mat4(1.0f)) override;

        /**
         * @brief Add a child mesh to the tree.
         * @param child A shared pointer to the MeshBase object to be added.
         */
        void addChild(std::shared_ptr<MeshBase> child);

        /**
         * @brief Get a child mesh by its index.
         * @param index The index of the child in the internal container.
         * @return std::shared_ptr<MeshBase> A shared pointer to the child mesh.
         */
        std::shared_ptr<MeshBase> getChild(std::size_t index) const;

    private:
        /// Internal container for children meshes.
        std::vector<std::shared_ptr<MeshBase>> _children;
    };
};