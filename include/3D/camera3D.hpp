#pragma once 

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "shader/shader.hpp"

namespace camera
{
	class Camera3D
	{
	public:
		glm::vec3 position;
		glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	
		bool firstClick = true;
	
		int width;
		int height;
	
		float speed = 0.1f;
		float sensitivity = 100.0f;
	
		Camera3D(int width, int height, glm::vec3 position);
	
		void update(float FOVdeg, float nearPlane, float farPlane, GLuint shaderID);
		void inputs(GLFWwindow* window);
	};

	Camera3D::Camera3D(int width, int height, glm::vec3 position)
	{
		this->width = width;
		this->height = height;
		this->position = position;
	}

	void Camera3D::update(float FOVdeg, float nearPlane, float farPlane, GLuint shaderID)
	{
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		view = glm::lookAt(position, position + orientation, up);
		projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

		glUniformMatrix4fv(
			glGetUniformLocation(shaderID, "cam"),
			1,
			GL_FALSE,
			glm::value_ptr(projection * view)
		);
	}

	void Camera3D::inputs(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			position += speed * orientation;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			position += speed * -glm::normalize(glm::cross(orientation, up));
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			position += speed * -orientation;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			position += speed * glm::normalize(glm::cross(orientation, up));
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			position += speed * up;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			position += speed * -up;
		}

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

			if (firstClick)
			{
				glfwSetCursorPos(window, (width / 2), (height / 2));
				firstClick = false;
			}

			double mouseX;
			double mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);

			float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
			float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

			glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, up)));

			if (abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
			{
				orientation = newOrientation;
			}

			orientation = glm::rotate(orientation, glm::radians(-rotY), up);

			glfwSetCursorPos(window, (width / 2), (height / 2));
		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			firstClick = true;
		}
	}
}

using namespace camera;