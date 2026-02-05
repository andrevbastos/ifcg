#include "ifcg/components/keys.hpp"

namespace ifcg
{
    void Keys::addKeyCallback(int key, const std::function<void()> callback)
    {
        _keyCallbacks[key].push_back(callback);
    }
    void Keys::update()
    {
        _justPressed.clear();
        _justReleased.clear();

        for (const auto& [key, callbacks] : _keyCallbacks) {
            int currentState = glfwGetKey(_window, key);
            
            if (currentState == GLFW_PRESS && _keyStates[key] == GLFW_RELEASE) {
                _justPressed[key] = true;
            }

            if (currentState == GLFW_RELEASE && _keyStates[key] == GLFW_PRESS) {
                _justReleased[key] = true;
            }

            _keyStates[key] = currentState;
        }
    }

    bool Keys::isKeyPressed(int key)
    {
        return _justPressed.count(key) && _justPressed[key];
    }

    bool Keys::isKeyReleased(int key)
    {
        return _justReleased.count(key) && _justReleased[key];
    }

    bool Keys::isKeyHeld(int key)
    {
        return glfwGetKey(_window, key) == GLFW_PRESS;
    }
    
    void Keys::processInput()
    {
        for (const auto& [key, callbacks] : _keyCallbacks) {
            for (const auto& callback : callbacks) {
                callback();
            }
        }
    }
};