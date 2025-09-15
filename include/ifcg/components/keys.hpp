/**
 * @file keys.hpp
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief Key input handling for the IFCG library.
 * @details This file declares the KeyInput class responsible for handling key input.
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <unordered_map>

namespace ifcg
{
	/**
	 * @class KeyInput
	 * @brief Class responsible for handling key input.
	 */
	class KeyInput
	{
	public:
        /**
         * @brief Add a callback for a specific key.
         * @param key The key to bind the callback to.
         * @param callback The function to call when the key is pressed.
         */
        void addKeyCallback(int key, const std::function<void()>& callback);

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
		/**
         * @brief Set the key state.
         * @param key The key to set.
         * @param state The state to set.
		 */
        void setKeyState(int key, bool state);

        // Key callbacks map.
        std::unordered_map<int, const std::function<void()>> _keyCallbacks;
        // Key states map.
		std::unordered_map<int, bool> _keyStates;
	};
};
