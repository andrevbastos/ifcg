#include "ifcg/components/keys.hpp"

namespace ifcg
{
    Keys::Keys(Window& win)
        : _window(win.getGLFWwindow())
    {
    }

    void Keys::addKeyCallback(Key key, KeyAction action, const std::function<void()> callback)
    {
        _callbacks[static_cast<int>(key)][action].push_back(callback);
    }

    void Keys::handleKeyEvent(int key, int action)
    {
        // Update internal state
        if (action == GLFW_PRESS) {
            _keyStates[key] = true;
        } else if (action == GLFW_RELEASE) {
            _keyStates[key] = false;
        }

        // Execute immediate callbacks (PRESS, RELEASE, REPEAT)
        KeyAction currentAction = static_cast<KeyAction>(action);
        if (_callbacks.count(key) && _callbacks[key].count(currentAction)) {
            for (const auto& callback : _callbacks[key][currentAction]) {
                callback();
            }
        }
    }

    void Keys::processInput()
    {
        // Execute continuous callbacks (HELD)
        for (auto const& [key, held] : _keyStates) {
            if (held) {
                if (_callbacks.count(key) && _callbacks[key].count(KeyAction::HELD)) {
                    for (const auto& callback : _callbacks[key][KeyAction::HELD]) {
                        callback();
                    }
                }
            }
        }
    }

    bool Keys::isKeyPressed(Key key) const
    {
        return isKeyHeld(key);
    }

    bool Keys::isKeyReleased(Key key) const
    {
        return !isKeyHeld(key);
    }

    bool Keys::isKeyHeld(Key key) const
    {
        auto it = _keyStates.find(static_cast<int>(key));
        if (it != _keyStates.end()) {
            return it->second;
        }
        return false;
    }
};
