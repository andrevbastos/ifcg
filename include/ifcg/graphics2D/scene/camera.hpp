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
	class Camera2D
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
	
		Camera2D(int width, int height);
	
		void update(float FOVdeg, float nearPlane, float farPlane, GLuint shaderID);
		void inputs(GLFWwindow* window);
	};
}

using namespace camera;