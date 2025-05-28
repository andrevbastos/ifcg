#pragma once 

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "ifcg/shader/shader.hpp"

namespace camera
{
	class Camera3D
	{
	public:
		Camera3D(int width, int height, glm::vec3 position);
		
		void update(float FOVdeg, float nearPlane, float farPlane, GLuint shaderID);
		void inputs(GLFWwindow* window);
		
		void translate(float t, glm::vec3 pos);
		void rotate(float angle, glm::vec3 axis);

		void setPos(glm::vec3 pos);

	private:
		glm::vec3 position;
		
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		
		bool firstClick = true;
		
		float pitch = 0.0f;
		
		int width;
		int height;
		
		float speed = 0.1f;
		float sensitivity = 100.0f;
	};
}

using namespace camera;