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

#include "shader/shader.hpp"
#include "2D/vertex2D.hpp"

#if defined(_WIN32) && defined(IFCG_BUILD_SHARED)
	#define IFCG_API __declspec(dllexport)
#elif defined(_WIN32) && !defined(IFCG_BUILD_SHARED)
	#define IFCG_API __declspec(dllimport)
#else
	#define IFCG_API
#endif

namespace ifcg
{
	// IFCG class

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

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

	IFCG* IFCG::instance = nullptr;
    GLFWwindow* IFCG::window = nullptr;

    IFCG::IFCG()
    {
        glfwInit();
    };

    void IFCG::init()
    {
        if (instance == nullptr)
        {
            instance = new IFCG();
            window = NULL;
        }
    };

    void IFCG::terminate()
    {
        if (instance != nullptr)
        {
            terminate_();
        }
    }

    void IFCG::createWindow(GLuint width, GLuint height)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        
        if (window == nullptr)
        {
            window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);

            if (window == nullptr)
            {
                std::cerr << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
            }
        }

        GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* vidMode = glfwGetVideoMode(primaryMonitor);
    
        int posX = (vidMode->width - width) / 2;
        int posY = (vidMode->height - height) / 2;
    
        glfwSetWindowPos(window, posX, posY);
        
        glfwFocusWindow(window);

        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }
    };

    void IFCG::destroyWindow()
    {
        if (window)
        {
            glfwDestroyWindow(window);
        } else {
            std::cerr << "Failed to destroy GLFW window" << std::endl;
        }
    };
    
    bool IFCG::shouldClose()
    {
        return glfwWindowShouldClose(IFCG::window);
    };

    void IFCG::clearBuffer(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    };

    void IFCG::readInputs()
    {
        glfwPollEvents();
        processInput();
    };

    void IFCG::processInput() 
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
    };

    void IFCG::swapBuffer()
    {
        glfwSwapBuffers(window);
    };

    Shader IFCG::getDefaultShader2D() {
        return Shader("../resources/shaders/default2D_vert.glsl", "../resources/shaders/default2D_frag.glsl");
    };

	Shader IFCG::getDefaultShader3D() {
        return Shader("../resources/shaders/default3D_vert.glsl", "../resources/shaders/default3D_frag.glsl");
    };

    void IFCG::terminate_() 
    {
        glfwTerminate();
    };
    
    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }    

	// !IFCG class
}; 	// end of namespace ifcg

using namespace ifcg;