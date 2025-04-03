#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "ifcg.hpp"

using namespace ifcg;

unsigned int width = 800;
unsigned int height = 600;

int main()
{
    IFCG::init();
    IFCG::createWindow(width, height);

    while (!IFCG::shouldClose())
    {
        IFCG::processInput();
        IFCG::clearBuffer(1.0f, 1.0f, 1.0f, 1.0f);

        IFCG::swapBuffer();
        IFCG::readInputs();
    }

    IFCG::terminate();
    return 0;
}