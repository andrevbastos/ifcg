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

#include <chrono>
#include <thread>

#include "ifcg/components/context.hpp"
#include "ifcg/components/window.hpp"
#include "ifcg/components/renderer.hpp"
#include "ifcg/components/keys.hpp"

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
		static void init(unsigned int w, unsigned int h, const char* title = "IFCG Window");

		/**
		 * @brief Setup the 2D rendering environment.
		 */
		static void setup2D();
		/**
		 * @brief Setup the 3D rendering environment.
		 */
		static void setup3D();

		/**
		 * @brief Get the Input Handler object.
		 * @return Keys* Pointer to the Keys object.
		 */
		static Keys* getInputHandler();

		/**
		 * @brief Get the Renderer object.
		 * @return Renderer* Pointer to the Renderer object.
		 */
		static Renderer* getRenderer();

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
		 * @brief Terminate the IFCG library and clean up resources.
		 */
		static void terminate();


	private:
		// Private constructor and destructor to enforce singleton pattern.
		IFCG(unsigned int w, unsigned int h, const char* title);
		~IFCG();
		IFCG(const IFCG&) = delete;
		IFCG& operator=(const IFCG&) = delete;

		// Singleton instance.
		static IFCG* _instance;

		// Target frame time in seconds (for FPS limiting).
		static double _frameTimeTarget; 

		// Components
		static Context* _context;
		static Window* _window;
		static Renderer* _renderer;
		static Keys* _keys;
	};
};

using namespace ifcg;