/**
 * @file meshTree.hpp
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief MeshTree3D class for managing a collection of 3D meshes.
 * @version 1.0
 * @date 2024-10-11
 */
#pragma once

#include <memory>
#include "ifcg/common/mesh.hpp"
#include "ifcg/graphics3D/geometry/mesh.hpp"

namespace mesh3D
{
    /**
     * @class MeshTree3D
     * @brief Class for managing a collection of 3D meshes.
     * @details This class allows grouping multiple Mesh3D objects into a single entity,
     *          enabling collective transformations and rendering.
     *          It inherits from the generic Mesh class defined in ifcg::Mesh.
     */
    class MeshTree3D : public ifcg::Mesh
    {
    public:
        /**
         * @brief Destroy the MeshTree3D object
         */
        ~MeshTree3D() = default;
        /**
         * @brief Construct a new MeshTree3D object
         * @param meshes Vector of pointers to Mesh objects to be included in the tree.
         */
	    MeshTree3D(const std::vector<Mesh*> &meshes);
        /**
         * @brief Copy constructor.
         * @param other The MeshTree3D object to copy.
         */
        MeshTree3D(const MeshTree3D &other);
        MeshTree3D* duplicate() const override;

        /**
         * @brief Draw the mesh tree.
         * @param m Model matrix to apply additionally to the mesh tree's own model matrix.
         */
        void draw(glm::mat4 m = glm::mat4(1.0f)) override;
        /**
         * @brief Enable or disable outline rendering for the mesh tree.
         * @param outline True to enable outline, false to disable.
         */
        void setOutline(bool outline);

        /**
         * @brief Translates the mesh tree.
         * @param tX X-axis translation.
         * @param tY Y-axis translation.
         * @param tZ Z-axis translation.
         */
        void translate(float tX, float tY, float tZ);
        /**
         * @brief Scales the mesh tree.
         * @param sX X-axis scale factor.
         * @param sY Y-axis scale factor.
         * @param sZ Z-axis scale factor.
         */
        void scale(float sX, float sY, float sZ);
        /**
         * @brief Rotates the mesh tree.
         * @param angle Angle in radians.
         * @param rX X-axis rotation amount over angle.
         * @param rY Y-axis rotation amount over angle.
         * @param rZ Z-axis rotation amount over angle.
         */
        void rotate(float angle, float rX, float rY, float rZ);
        /**
         * @brief Reflects the mesh tree over the given axes.
         * @param refX X-axis reflection.
         * @param refY Y-axis reflection.
         * @param refZ Z-axis reflection.
         */
        void reflect(bool refX, bool refY, bool refZ);

        // Sub-mesh management
        void addSubMesh(Mesh* mesh);
        // Returns a pointer to the sub-mesh at the specified index. Returns nullptr if index is out of range.
        Mesh* getSubMesh(int index) const;

        // Model transformation matrix for the entire mesh tree.
        glm::mat4 model = glm::mat4(1.0f);

    private:
        // Collection of sub-meshes
		std::vector<Mesh*> subMeshes;
        
        // Outline rendering flag.
        bool outline = false;
    };
};

using namespace mesh3D;