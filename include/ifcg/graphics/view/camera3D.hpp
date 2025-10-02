/**
 * @file camera3D.hpp
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief Camera3D class for representing a 3D camera.
 * @copyright Copyright (c) 2025
 */
#pragma once

#include "ifcg/common/cameraBase.hpp"

namespace ifcg
{
	class Camera3D : public Camera
	{
	public:
		/**
		 * @brief Destroy the Camera3D object
		 */
		~Camera3D() = default;
		/**
		 * @brief Construct a new Camera3D object
		 * @param width Width of the viewport.
		 * @param height Height of the viewport.
		 */
		Camera3D(int width, int height);
		
		/**
		 * @brief Update the camera's projection and view matrices.
		 * @param FOVdeg Field of view in degrees.
		 * @param nearPlane Near clipping plane distance.
		 * @param farPlane Far clipping plane distance.
		 * @param shaderID Shader program ID to update with the camera matrices.
		 */
		void update(float FOVdeg, float nearPlane, float farPlane, GLuint shaderID);
		/**
		 * @brief Process input events to control the camera.
		 * @param window Pointer to the GLFW window for capturing input.
		 */
		void inputs(GLFWwindow* window);
		/**
		 * @brief Set the camera's position in 3D space.
		 * @param pos New position vector for the camera.
		 */
		void setPos(glm::vec3 pos);

		/**
		 * @brief Get the camera's projection matrix.
		 * @return glm::mat4 The projection matrix.
		 */
		glm::mat4 getProjectionMatrix();
		/**
		 * @brief Get the camera's view matrix.
		 * @return glm::mat4 The view matrix.
		 */
		glm::mat4 getViewMatrix();
		
	private:
		// Helper methods for camera transformations
		void translate(float t, glm::vec3 pos);
		void rotate(float angle, glm::vec3 axis);
		
		// Camera attributes
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		
		glm::mat4 projection = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);

		// Mouse control attributes
		bool firstClick = true;
		
		// Euler angles
		float yaw = -90.0f;
		float pitch = 0.0f;
		
		// Viewport dimensions
		int width;
		int height;
		
		// Movement parameters
		float speed = 0.1f;

		// Mouse sensitivity
		float sensitivity = 100.0f;
	};
};