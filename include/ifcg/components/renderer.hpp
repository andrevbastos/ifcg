/**
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief Renderer component for the IFCG library.
 * @details This file declares the Renderer class responsible for rendering 2D and 3D graphics.
 * @version 0.1
 * @date 2025-09-14
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <functional>
#include <vector>
#include <algorithm>
#include <iostream>

#include "ifcg/components/window.hpp"
#include "ifcg/common/meshBase.hpp"
#include "ifcg/common/cameraBase.hpp"
#include "ifcg/graphics/view/camera2D.hpp"
#include "ifcg/graphics/view/camera3D.hpp"
#include "ifcg/shader/shader.hpp"

namespace ifcg
{
	/**
	 * @class Renderer
	 * @brief Class responsible for rendering graphics.
	 */
	class Renderer
	{
	public:
		/**
		 * @brief Construct a new Renderer object.
		 * @param win Pointer to the associated Window object.
		 */
        Renderer(Window* win);

		/**
		 * @brief Setup the 2D rendering environment.
		 */
		void setup2D();
		/**
		 * @brief Setup the 3D rendering environment.
		 */
		void setup3D();

        /**
		 * @brief Adds a mesh to the render queue.
		 * @param mesh Pointer to the mesh to be added.
		 */
		void addMesh(MeshBase* mesh);
		/**
		 * @brief Removes a mesh from the render queue.
		 * @param mesh Pointer to the mesh to be removed.
		 */
		void removeMesh(MeshBase* mesh);
        /**
         * @brief Clear the color and depth buffers with the given color.
         * @param r Red component (0.0f to 1.0f).
         * @param g Green component (0.0f to 1.0f).
         * @param b Blue component (0.0f to 1.0f).
         * @param a Alpha component (0.0f to 1.0f). Default is 1.0f.
         */
        void clearBuffer(float r, float g, float b, float a = 1.0f);
        /**
         * @brief Swap the front and back buffers of the current window.
         */
        void swapBuffer();
		/**
		 * @brief Render all meshes in the render queue.
		 */
		void render();
		/**
		 * @brief Clear the render queue and reset the renderer state.
		 */
		void reset();

		/**
		 * @brief Get the OpenGL shader program ID.
		 * @return unsigned int Shader program ID.
		 */
		unsigned int getShaderID() const;
		/**
		 * @brief Set the active shader program.
		 * @param shader Pointer to the Shader object.
		 */
		void setShader(Shader* shader);

		/**
		 * @brief Set the active camera for 3D rendering.
		 * @param cam Pointer to the Camera object.
		 */
		void setCamera(Camera* cam);
		/**
		 * @brief Get the active camera for 3D rendering.
		 * @return Pointer to the Camera object.
		 */
		Camera* getCamera() const;

	private:
        /**
		 * @brief Render queue holding all meshes to be drawn each frame.
		 * @details Meshes can be added or removed from this queue using addMesh and removeMesh methods.
		 */
		std::vector<MeshBase*> _renderQueue;
		
        // Pointer to the current shader program.
		Shader* _shader;
        // Pointer to the active camera for 3D rendering.
        Camera* _camera;
        // Pointer to the associated window for rendering context.    
        Window* _window;
    };
};
