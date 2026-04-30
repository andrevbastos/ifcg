/**
 * @file camera.hpp
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief Header file for the Camera class.
 * @details This file defines the Camera class, which manages 3D view and projection 
 *          matrices, handling user input for movement and rotation.
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
	 * @brief Represents a 3D camera for navigating the scene.
	 * @details The Camera class computes the view and projection matrices used by OpenGL shaders.
	 *          It supports basic movement (WASD), elevation, and mouse-based look-around.
	 */
	class Camera
	{
	public:
		/**
		 * @brief Destroy the Camera object.
		 */
		~Camera() = default;

		/**
		 * @brief Construct a new Camera object.
		 * @param width Width of the viewport in pixels.
		 * @param height Height of the viewport in pixels.
		 */
		Camera(int width, int height);
		
		/**
		 * @brief Update the camera's projection and view matrices and send them to the shader.
		 * @param FOVdeg Field of view in degrees.
		 * @param nearPlane Near clipping plane distance.
		 * @param farPlane Far clipping plane distance.
		 * @param shaderID Shader program ID to update with the camera matrices.
		 */
		void update(float FOVdeg, float nearPlane, float farPlane, GLuint shaderID);

		/**
		 * @brief Process keyboard and mouse input events to control the camera.
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
		
		/**
		 * @brief Translate the camera by a specific amount in a given direction.
		 * @param t Scalar amount of translation.
		 * @param pos Direction vector for the translation.
		 */
		void translate(float t, glm::vec3 pos);

		/**
		 * @brief Rotate the camera around a specific axis.
		 * @param angle Angle in radians.
		 * @param axis Axis vector to rotate around.
		 */
		void rotate(float angle, glm::vec3 axis);

		/**
		 * @brief Get the current movement speed of the camera.
		 * @return float The camera's speed.
		 */
		float getSpeed() const;

		/**
		 * @brief Set a new movement speed for the camera.
		 * @param newSpeed The new speed value.
		 */
		void setSpeed(float newSpeed);

	private:
		/// Camera position in world space.
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
		/// Camera orientation (look-at) vector.
		glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		/// Camera up vector.
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		
		/// Precomputed projection matrix.
		glm::mat4 projection = glm::mat4(1.0f);
		/// Precomputed view matrix.
		glm::mat4 view = glm::mat4(1.0f);

		/// Flag to handle the first mouse interaction correctly.
		bool firstClick = true;
		
		/// Euler angle for horizontal rotation.
		float yaw = -90.0f;
		/// Euler angle for vertical rotation.
		float pitch = 0.0f;
		
		/// Viewport width.
		int width;
		/// Viewport height.
		int height;
		
		/// Movement speed multiplier.
		float speed = 0.1f;

		/// Mouse sensitivity multiplier.
		float sensitivity = 100.0f;
	};
};