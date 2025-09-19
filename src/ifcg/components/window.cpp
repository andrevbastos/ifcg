#include "ifcg/components/window.hpp"

namespace ifcg
{
    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }   

    Window::Window(unsigned int width, unsigned int height, const char* title)
        : _width(width), _height(height), _window(nullptr)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        
        if (!_window)
        {
            _window = glfwCreateWindow(width, height, title, NULL, NULL);

            if (!_window)
            {
                std::cerr << "Failed to create GLFW _window" << std::endl;
                glfwTerminate();
            }
        }

        GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* vidMode = glfwGetVideoMode(primaryMonitor);
    
        int posX = (vidMode->width - width) / 2;
        int posY = (vidMode->height - height) / 2;

        glfwSetWindowPos(_window, posX, posY);

        glfwFocusWindow(_window);

        glfwMakeContextCurrent(_window);
        glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }
    }

    Window::~Window()
    {
        if (_window)
        {
            glfwDestroyWindow(_window);
            glfwTerminate();
        } else {
            std::cerr << "Failed to destroy GLFW _window" << std::endl;
        }
    }
    
    bool Window::shouldClose() const
    {
        return _window ? glfwWindowShouldClose(_window) : true;
    }

    GLFWwindow* Window::getGLFWwindow() const
    {
        return _window;
    }

    unsigned int Window::getHeight() const
    {
        return _height;
    }

    unsigned int Window::getWidth() const
    {
        return _width;
    }
};