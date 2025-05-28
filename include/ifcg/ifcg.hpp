#pragma once

/**
* \author André B.
* \date March 20, 2025
* \version March 20, 2025
* \brief Constructor for IFCG class using Singleton pattern
**/

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "ifcg/shader/shader.hpp"

#if defined(_WIN32) && defined(IFCG_BUILD_SHARED)
	#define IFCG_API __declspec(dllexport)
#elif defined(_WIN32) && !defined(IFCG_BUILD_SHARED)
	#define IFCG_API __declspec(dllimport)
#else
	#define IFCG_API
#endif

namespace ifcg
{
    class IFCG
	{
	public:
		static void init();
		
		static void createWindow(GLuint width, GLuint height);
		static void destroyWindow();
		static bool shouldClose();
    	static void clearBuffer(float r, float g, float b, float a = 1.0f);
		static void readInputs();
		static void processInput();
		static void swapBuffer();
		
		static Shader getDefaultShader2D();
		static Shader getDefaultShader3D();

		static void terminate();

		static GLFWwindow* window;

	private:
		IFCG();
		static void terminate_();
		
		static IFCG* instance;
	};
};

using namespace ifcg;