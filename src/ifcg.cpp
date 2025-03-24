#include "ifcg.hpp"
#include <iostream>

IFCG* IFCG::instance = nullptr;
GLFWwindow* IFCG::window = nullptr;

IFCG::IFCG()
{
    glfwInit();
}

IFCG* IFCG::init()
{
    if (instance == nullptr)
    {
        instance = new IFCG();
        window = NULL;
    }
    return instance;
}

void IFCG::createWindow(GLuint width, GLuint height)
{
    if (window == nullptr)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);

        if (window == nullptr)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }
    }

    glfwMakeContextCurrent(window);
}

void IFCG::createViewport(GLuint width, GLuint height)
{
	gladLoadGL();
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
}