/**
 * @file keys.hpp
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief Key input handling for the IFCG library using an event-driven architecture.
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <unordered_map>
#include <functional>
#include <vector>

#include "ifcg/components/window.hpp"
#include "ifcg/components/keys_list.hpp"

namespace ifcg
{
	/**
	 * @class Keys
	 * @brief Class responsible for handling key input via events and continuous polling for held states.
	 */
	class Keys
	{
	public:
		/**
		 * @brief Construct a new Keys object.
		 * @param win The window to associate with this key handler.
		 */
		Keys(Window& win);
		
        /**
         * @brief Add a callback for a specific key and action.
         * @param key The key to bind the callback to.
         * @param action The action that triggers the callback.
         * @param callback The function to call when the key action occurs.
         */
        void addKeyCallback(Key key, KeyAction action, const std::function<void()> callback);

		/**
		 * @brief Handle a key event from GLFW.
		 * @param key The key that was pressed/released.
		 * @param action The action (PRESS, RELEASE, REPEAT).
		 */
		void handleKeyEvent(int key, int action);

        /**
         * @brief Process continuous input events (HELD). Should be called each frame.
         */
        void processInput();

		/**
		 * @brief Check if a key was pressed in the last event.
		 * @param key The key to check.
		 * @return true if pressed, false otherwise.
		 */
		bool isKeyPressed(Key key) const;

		/**
		 * @brief Check if a key was released in the last event.
		 * @param key The key to check.
		 * @return true if released, false otherwise.
		 */
		bool isKeyReleased(Key key) const;

		/**
		 * @brief Check if a key is currently held down.
		 * @param key The key to check.
		 * @return true if held, false otherwise.
		 */
		bool isKeyHeld(Key key) const;

	private:
		// Pointer to the GLFW window.
		GLFWwindow* _window;

        // Key callbacks map: Key (int) -> {Action -> List of Callbacks}
        std::unordered_map<int, std::unordered_map<KeyAction, std::vector<std::function<void()>>>> _callbacks;
        
        // Internal state to track held keys.
		std::unordered_map<int, bool> _keyStates;
	};
};
