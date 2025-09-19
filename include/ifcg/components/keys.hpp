/**
 * @file keys.hpp
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief Key input handling for the IFCG library.
 * @details This file declares the KeyInput class responsible for handling key input.
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <unordered_map>
#include <functional>
#include <vector>

#include "ifcg/components/window.hpp"

namespace ifcg
{
	/**
	 * @class Keys
	 * @brief Class responsible for handling key input.
	 */
	class Keys
	{
	public:
		/**
		 * @brief Construct a new Keys object.
		 * @param win The window to associate with this key handler.
		 */
		Keys(Window* win) 
			: _window(win->getGLFWwindow()) {};
        /**
         * @brief Add a callback for a specific key.
         * @param key The key to bind the callback to.
         * @param callback The function to call when the key is pressed.
         */
        void addKeyCallback(int key, const std::function<void()> callback);

		/**
		 * @brief Update the key states. Should be called each frame.
		 */
		void update();

		/**
		 * @brief Get the state of a key.
		 * @param key The key to check.
		 * @return The state of the key.
		 */
		int getKeyState(int key) const;

		/**
		 * @brief Get the state of a key.
		 * @param key The key to check.
		 * @return true if the key is pressed, false otherwise.
		 */
		bool isKeyPressed(int key);
		/**
		 * @brief Get the state of a key.
		 * @param key The key to check.
		 * @return true if the key is released, false otherwise.
		 */
		bool isKeyReleased(int key);
		/**
		 * @brief Get the state of a key.
		 * @param key The key to check.
		 * @return true if the key is held, false otherwise.
		 */
		bool isKeyHeld(int key);
        /**
         * @brief Process input events.
         */
        void processInput();

	private:
		// Pointer to the GLFW window.
		GLFWwindow* _window;
        // Key callbacks map.
        std::unordered_map<int, std::vector<std::function<void()>>> _keyCallbacks;
        // Key states map.
		std::unordered_map<int, int> _keyStates;

		// Just pressed and just released states for edge detection.
		std::unordered_map<int, bool> _justPressed;
        std::unordered_map<int, bool> _justReleased;
	};
};
