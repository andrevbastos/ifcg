#ifndef IFCH_H
#define IFCG_H

/**
* \author André B.
* \date March 20, 2025
* \version March 20, 2025
* \brief Constructor for IFCG class using Singleton pattern
**/

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "mesh.hpp"
#include "shader.hpp"

#if defined(_WIN32) && defined(IFCG_BUILD_SHARED)
    #define IFCG_API __declspec(dllexport)
#elif defined(_WIN32) && !defined(IFCG_BUILD_SHARED)
    #define IFCG_API __declspec(dllimport)
#else
    #define IFCG_API
#endif

class IFCG
{
public:
	static IFCG* init();
	static GLFWwindow* window;

	static void createWindow(GLuint width, GLuint height);
	static void createViewport(GLuint width, GLuint height);
	static void clearBuffer();
	static void readInputs(GLFWwindow* window);
	static void processInput(GLFWwindow *window);

	static std::vector<Vertex> cubeVertex();
	static std::vector<GLuint> cubeIndex();
	static std::vector<Vertex> pyramidVertex();
	static std::vector<GLuint> pyramidIndex();

private:
	static IFCG* instance;
	IFCG();
};

#endif
