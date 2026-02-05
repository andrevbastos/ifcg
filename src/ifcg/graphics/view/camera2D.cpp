#include "ifcg/graphics/view/camera2D.hpp"

namespace ifcg
{
	Camera2D::Camera2D(int w, int h)
		: width(w), height(h) {}

	void Camera2D::update(float FOVdeg, float nearPlane, float farPlane, GLuint shaderID)
	{	
		view = glm::lookAt(position, position + orientation, up);
		projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

		glUniformMatrix4fv(
			glGetUniformLocation(shaderID, "projection"),
			1,
			GL_FALSE,
			glm::value_ptr(projection)
		);
		glUniformMatrix4fv(
			glGetUniformLocation(shaderID, "view"),
			1,
			GL_FALSE,
			glm::value_ptr(view)
		);
	}

	void Camera2D::inputs(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			translate(speed, orientation);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			translate(speed, -glm::normalize(glm::cross(orientation, up)));
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			translate(speed, -orientation);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			translate(speed, glm::normalize(glm::cross(orientation, up)));
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			translate(speed, up);
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			translate(speed, -up);
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			translate(speed, glm::normalize(glm::cross(orientation, up)));
			rotate(glm::radians(1.0f), up);
		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			translate(speed, -glm::normalize(glm::cross(orientation, up)));
			rotate(glm::radians(-1.0f), up);
		}

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			if (firstClick)
			{
				glfwSetCursorPos(window, (width / 2), (height / 2));
				firstClick = false;
			}

			double mouseX;
			double mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);

			float xoffset = sensitivity * (float)(mouseY - (height / 2)) / height;
			float yoffset = sensitivity * (float)(mouseX - (width / 2)) / width;

			pitch += glm::radians(-xoffset);

			if (pitch >= 1)
				pitch = 1;
			if (pitch <= -1)
				pitch = -1;

			if (abs(pitch) != 1.0f) {
				rotate(glm::radians(-xoffset), glm::normalize(glm::cross(orientation, up)));
			}

			rotate(glm::radians(-yoffset), up);

			glfwSetCursorPos(window, (width / 2), (height / 2));
		} else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			firstClick = true;
		}
	};

	void Camera2D::setPos(glm::vec3 pos)
	{
		position = pos;
	};

	void Camera2D::translate(float amount, glm::vec3 target)
	{
		position += amount * target;
	};

	void Camera2D::rotate(float angle, glm::vec3 axis)
	{
		orientation = glm::rotate(orientation, angle, axis);
	};

	glm::mat4 Camera2D::getProjectionMatrix()
	{
		return projection;
	};

	glm::mat4 Camera2D::getViewMatrix()
	{
		return view;
	};
}