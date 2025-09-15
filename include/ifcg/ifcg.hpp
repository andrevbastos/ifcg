/**
 * @file ifcg.hpp
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief Main header file for the IFCG library.
 * @details This file includes all necessary headers and declares the main IFCG class for initializing and
 * 			managing the graphics context, window, rendering loop, and scene setup.
 * @version 0.1
 * @date 2025-09-14
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <functional>
#include <thread>
#include <chrono>

#include "ifcg/shader/shader.hpp"
#include "ifcg/common/mesh.hpp"
#include "ifcg/common/camera.hpp"

#include "ifcg/graphics2D/scene/camera.hpp"
#include "ifcg/graphics3D/scene/camera.hpp"
#include "ifcg/graphics2D/geometry/mesh.hpp"
#include "ifcg/graphics3D/geometry/mesh.hpp"

namespace ifcg
{
	/**
	 * @class IFCG
	 * @brief Wrapper class for initializing and managing the IFCG graphics context.
	 */
    class IFCG
	{
	public:
		/**
		 * @brief Singleton initialization method.
		 */
		static void init();

		/**
		 * @brief Set the FramesPerSecond used in the main loop.
		 * @param fps Frames per second (0 for uncapped).
		 */
		static void setFramesPerSecond(int fps);
		/**
		 * @brief Run the main application loop.
		 * @param gameLoopBody Function to be called each loop iteration.
		 */
        static void loop(const std::function<void()>& loopBody);
		/**
		 * @brief Create a Window object with given width and height
		 * @param w Window width
		 * @param h Window height
		 */
		static void createWindow(GLuint w, GLuint h);
		/**
		 * @brief Destroy the Window object.
		 */
		static void destroyWindow();
		/**
		 * @brief Test if the current window should close.
		 * @return true 
		 * @return false 
		 */
		static bool shouldClose();
		/**
		 * @brief Clear the color and depth buffers with the given color.
		 * @param r Red component (0.0f to 1.0f).
		 * @param g Green component (0.0f to 1.0f).
		 * @param b Blue component (0.0f to 1.0f).
		 * @param a Alpha component (0.0f to 1.0f). Default is 1.0f.
		 */
    	static void clearBuffer(float r, float g, float b, float a = 1.0f);
		/**
		 * @brief Capture current window input events.
		 */
		static void readInputs();
		/**
		 * @brief Process input events.
		 */
		static void processInput();
		/**
		 * @brief Swap the front and back buffers of the current window.
		 */
		static void swapBuffer();
		
		/**
		 * @brief Setup the 2D rendering environment.
		 */
		static void setup2D();
		/**
		 * @brief Setup the 3D rendering environment.
		 */
		static void setup3D();

		/**
		 * @brief Adds a mesh to the render queue.
		 * @param mesh Pointer to the mesh to be added.
		 */
		static void addMesh(Mesh* mesh);
		/**
		 * @brief Removes a mesh from the render queue.
		 * @param mesh Pointer to the mesh to be removed.
		 */
		static void removeMesh(Mesh* mesh);
		/**
		 * @brief Render all meshes in the render queue.
		 */
		static void render();

		/**
		 * @brief Terminates all IFCG systems and releases resources.
		 */
		static void terminate();
		
		// Window and rendering context.
		static GLFWwindow* window;
		// Current active camera.
		static Camera* camera;
		// Current shader program.
		static Shader shader;
		
		/**
		 * @brief Render queue holding all meshes to be drawn each frame.
		 * @details Meshes can be added or removed from this queue using addMesh and removeMesh methods.
		 */
		static std::vector<Mesh*> renderQueue;
		// Current window dimensions.
		static GLuint width;
		static GLuint height;
	private:
		// Private constructor for singleton pattern.
		IFCG();
		// Private destructor.
		static void terminate_();
		
		// Singleton instance.
		static IFCG* instance;
		// Target frame time in seconds (for FPS limiting).
		static double frameTimeTarget; 
	};
};

using namespace ifcg;