#include "ifcg/components/window.hpp"

namespace ifcg
{
    void framebuffer_size_callback(GLFWwindow* /*window*/, int width, int height)
    {
        glViewport(0, 0, width, height);
    }   

    Window::Window(unsigned int width, unsigned int height, const char* title)
        : _width(width), _height(height) {
        _window = nullptr;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE);
        glfwWindowHint(GLFW_ALPHA_BITS, 0);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE); 

        glfwWindowHintString(GLFW_X11_CLASS_NAME, "ifcg_opengl");
        glfwWindowHintString(GLFW_X11_INSTANCE_NAME, "ifcg_opengl");
        #ifdef GLFW_WAYLAND_APP_ID
            glfwWindowHintString(GLFW_WAYLAND_APP_ID, "ifcg_opengl");
        #endif

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
        glfwGetVideoMode(primaryMonitor);

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