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

	private:
		// Private constructor and destructor to enforce singleton pattern.
		IFCG() = default;
		~IFCG() = default;
		IFCG(const IFCG&) = delete;
		IFCG& operator=(const IFCG&) = delete;


		// Singleton instance.
		static IFCG* _instance;

		// Target frame time in seconds (for FPS limiting).
		static double _frameTimeTarget; 
	};
};

using namespace ifcg;