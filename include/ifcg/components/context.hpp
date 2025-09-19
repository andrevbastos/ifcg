/**
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief Context management for the IFCG library.
 * @details This file declares the Context class responsible for managing the rendering context.
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace ifcg
{
	/**
	 * @class Context
	 * @brief Class responsible for managing the rendering context.
	 */
	class Context
	{
	public:
		/**
		 * @brief Initialize the rendering context.
		 * @param window Pointer to the window object.
		 */
		Context();
		/**
		 * @brief Poll for and process events.
		 */
		void pollEvents();
        /**
         * @brief Get the time since the context was initialized.
         * @return The time in seconds.
         */
        double getTime();
        /**
         * @brief Terminate the context.
         */
        void terminate();

        /**
         * @brief Load the OpenGL function pointers using GLAD.
         */
        void loadGlad();
	};
};
