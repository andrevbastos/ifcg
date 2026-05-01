/**
 * @file ifcg.hpp
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief Main header file for the IFCG library.
 * @details This file includes all necessary headers and declares the main Engine class for initializing and
 * 			managing the graphics context, window, rendering loop, and scene setup.
 * @version 0.1
 * @date 2025-09-14
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <chrono>
#include <thread>
#include <stop_token>
#include <functional>
#include <memory>

#include "ifcg/components/context.hpp"
#include "ifcg/components/window.hpp"
#include "ifcg/components/renderer.hpp"
#include "ifcg/components/keys.hpp"

namespace ifcg
{
	/**
	 * @struct LoopConfig
	 * @brief Configuration struct for the main loop, allowing users to specify callbacks for different stages of the loop.
	 * @details Users can provide custom functions to be called before the loop starts, before and after input processing,
	 * 			during the main loop body, after rendering, and when exiting the
	 */
	struct LoopConfig {
		const std::function<void()>& beforeLoop = [] {};
		const std::function<void()>& beforeInputs = [] {};
		const std::function<void()>& afterInputs = [] {};
		const std::function<void()>& loopBody = [] {};
		const std::function<void()>& afterRender = [] {};
		const std::function<void()>& onExit = [] {};
	};

	/**
	 * @class Engine
	 * @brief Wrapper class for initializing and managing the IFCG graphics context.
	 */
    class Engine
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
		static Engine* _instance;
		 */
		static Keys& getInputHandler();

		/**
		 * @brief Get the Renderer object.
		 * @return Renderer& Reference to the Renderer object.
		 */
		static Renderer& getRenderer();

		/**
		 * @brief Check if the application window is still running.
		 * @return true if the window should remain open, false otherwise.
		 */
		static bool isRunning();

		/**
		 * @brief Poll and process window events.
		 */
		static void pollEvents();

		/**
		 * @brief Release the OpenGL context from the current thread.
		 */
		static void releaseContext();

		/**
		 * @brief Set the FramesPerSecond used in the main loop.
		 * @param fps Frames per second (0 for uncapped).
		 */
		static void setFramesPerSecond(int fps);
		/**
		 * @brief Run the main application loop.
		 * @param gameLoopBody Function to be called each loop iteration.
		 */
        static void loop(LoopConfig config);
		/**
		 * @brief Internal loop function that runs in a separate thread.
		 * @param token Stop token for gracefully exiting the loop.
		 * @param config Loop configuration containing callbacks and conditions.
		 */
		static void loopP(std::stop_token token, LoopConfig config);
		/**
		 * @brief Terminate the IFCG library and clean up resources.
		 */
		static void terminate();


	private:
		// Concede permissão para o unique_ptr conseguir destruir o Singleton
        friend struct std::default_delete<Engine>;

        // Private constructor and destructor
        Engine(unsigned int w, unsigned int h, const char* title);
        ~Engine();
		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;

		// Singleton instance.
		static std::unique_ptr<Engine> _instance;

		// Target frame time in seconds (for FPS limiting).
		static double _frameTimeTarget; 

		// Components
		static std::unique_ptr<Context> _context;
		static std::unique_ptr<Window> _window;
		static std::unique_ptr<Renderer> _renderer;
		static std::unique_ptr<Keys> _keys;
	};
};