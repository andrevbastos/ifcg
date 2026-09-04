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
#include <queue>
#include <mutex>
#include <utility>
#include <type_traits>

#include "ifcg/components/context.hpp"
#include "ifcg/components/window.hpp"
#include "ifcg/components/renderer.hpp"
#include "ifcg/components/keys.hpp"
#include "ifcg/components/task.hpp"

namespace ifcg
{
	/**
	 * @enum LoopMode
	 * @brief Defines how the engine loop should use worker threads.
	 */
	enum class LoopMode {
		Sequential,
		Concurrent
	};

	/**
	 * @struct LoopConfig
	 * @brief Configuration struct for the main loop, allowing users to specify callbacks for different stages of the loop.
	 * @details Users can provide custom functions to be called before the loop starts, before and after input processing,
	 * 			during the main loop body, after rendering, and when exiting the
	 */
	struct LoopConfig {
		const LoopMode mode = LoopMode::Sequential;
		const std::function<void()> beforeLoop = [] {};
		const std::function<void()> beforeInputs = [] {};
		const std::function<void()> afterInputs = [] {};
		const std::function<void()> loopBody = [] {};
		const std::function<void()> afterRender = [] {};
		const std::function<void()> onExit = [] {};
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
		 * @brief Get the Context object.
		 * @return Context& Reference to the Context object.
		 */
		static Context& getContext();
		
		/**
		 * @brief Get the Window object.
		 * @return Window& Reference to the Window object.
		 */
		static Window& getWindow();

		/**
		 * @brief Get the Input Handler object.
		 * @return Keys* Pointer to the Keys object.
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
		 * @brief Check whether the current code is running on the engine main/render thread.
		 */
		static bool isMainThread();

		/**
		 * @brief Get the worker task manager.
		 */
		static TaskMaster& getTaskMaster();

		/**
		 * @brief Queue work to be executed by a worker thread.
		 */
		template <typename Func>
		static void runAsync(Func&& task, Priority p = Priority::Medium) {
			getTaskMaster().addTask(std::forward<Func>(task), p);
		}

		/**
		 * @brief Run work on the main/render thread.
		 * @details If already on the main thread, the task runs immediately. Otherwise,
		 *          it is queued and processed by Engine::loop.
		 */
		template <typename Func>
		static void runOnMainThread(Func&& task) {
			if (isMainThread()) {
				std::forward<Func>(task)();
				return;
			}

			{
				std::lock_guard<std::mutex> lock(_mainThreadQueueMutex);
				_mainThreadQueue.push(std::function<void()>(std::forward<Func>(task)));
			}
		}

		/**
		 * @brief Run a CPU task on a worker and send its result back to the main/render thread.
		 * @details The worker function runs outside the main thread. The main function runs
		 *          later on Engine::loop, receiving the worker result when the worker returns
		 *          a value. Void workers are also supported.
		 */
		template <typename WorkerFunc, typename MainFunc>
		static void runAsyncThenMain(WorkerFunc&& workerFunc, MainFunc&& mainFunc, Priority p = Priority::Medium) {
			using Worker = std::decay_t<WorkerFunc>;
			using Main = std::decay_t<MainFunc>;

			auto worker = std::make_shared<Worker>(std::forward<WorkerFunc>(workerFunc));
			auto main = std::make_shared<Main>(std::forward<MainFunc>(mainFunc));

			runAsync([worker, main]() mutable {
				if constexpr (std::is_void_v<std::invoke_result_t<Worker&>>) {
					std::invoke(*worker);
					runOnMainThread([main]() mutable {
						std::invoke(*main);
					});
				} else {
					auto result = std::invoke(*worker);
					auto sharedResult = std::make_shared<decltype(result)>(std::move(result));

					runOnMainThread([main, sharedResult]() mutable {
						std::invoke(*main, std::move(*sharedResult));
					});
				}
			}, p);
		}
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

		// Main/render thread support.
		static std::thread::id _mainThreadId;
		static std::queue<std::function<void()>> _mainThreadQueue;
		static std::mutex _mainThreadQueueMutex;
		static void processMainThreadTasks();

		// Components
		static std::unique_ptr<Context> _context;
		static std::unique_ptr<Window> _window;
		static std::unique_ptr<Renderer> _renderer;
		static std::unique_ptr<Keys> _keys;
		static std::unique_ptr<TaskMaster> _taskMaster;
	};
};