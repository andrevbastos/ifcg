#pragma once

#include "ifcg/common/camera.hpp"

class Camera2D : public Camera
{
public:
    Camera2D(unsigned int width, unsigned int height) {};

    ~Camera2D() = default;

    void update(float FOVdeg, float nearPlane, float farPlane, GLuint shaderID) {};
    void inputs(GLFWwindow* window) {};
    void setPos(glm::vec3 pos) {};

    glm::mat4 getProjectionMatrix() { return glm::mat4(1.0f); };
    glm::mat4 getViewMatrix() { return glm::mat4(1.0f); };
};