#include "ifcg/components/context.hpp"

namespace ifcg 
{
    Context::Context()
    {
        if (!glfwInit())
        {
            throw std::runtime_error("Failed to initialize GLFW");
        }
    }

    void Context::pollEvents()
    {
        glfwPollEvents();
    }

    double Context::getTime()
    {
        return glfwGetTime();
    }

    void Context::terminate()
    {
        glfwTerminate();
    }
};