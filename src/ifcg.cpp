#include "ifcg.hpp"
#include <iostream>

namespace ifcg
{
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
        
        if (window == nullptr)
        {
            window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);

            if (window == nullptr)
            {
                std::cerr << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
            }
        }
        
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
        return Shader("../resources/shaders/default.vert", "../resources/shaders/default.frag");
    };

    void IFCG::terminate_() 
    {
        glfwTerminate();
    };
    
    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }   

}; // end of namespace ifcg