/**
 * @file camera.hpp
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief Camera interface for 2D and 3D scenes.
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "ifcg/shader/shader.hpp"

namespace ifcg
{
    /**
     * @class Camera
     * @brief Abstract base class for camera implementations in 2D and 3D scenes.
     * @details This class defines the interface for camera operations such as updating
     * projection and view matrices, handling user inputs, and setting position.
     */
    class Camera
    {
    public:
        virtual ~Camera() = default;

        virtual void update(float FOVdeg, float nearPlane, float farPlane, GLuint shaderID) = 0;
        virtual void inputs(GLFWwindow* window) = 0;
		virtual void setPos(glm::vec3 pos) = 0;

        virtual glm::mat4 getProjectionMatrix() = 0;
        virtual glm::mat4 getViewMatrix() = 0;
    };
}