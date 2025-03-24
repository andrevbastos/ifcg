#ifndef IFCH_H
#define IFCG_H

/**
* \author André B.
* \date March 20, 2025
* \version March 20, 2025
* \brief Constructor for IFCG class using Singleton pattern
**/

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
	static void createWindow(GLuint width, GLuint height);
	static void createViewport(GLuint width, GLuint height);
	static GLFWwindow* window;
	static IFCG* init();
private:
	static IFCG* instance;
	IFCG();
};

#endif
