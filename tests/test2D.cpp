#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ifcg/ifcg.hpp"
#include "ifcg/graphics2D/scene/camera.hpp"
#include "ifcg/graphics2D/geometry/square.hpp"

unsigned int width = 800;
unsigned int height = 600;

int main()
{
    IFCG::init();
    IFCG::createWindow(width, height);

    IFCG::setup2D();

    Square2D square(IFCG::shader.id);

    IFCG::addMesh(&square);

    while (!IFCG::shouldClose())
    {
        IFCG::readInputs();
        IFCG::processInput();
        IFCG::clearBuffer(1.0f, 1.0f, 1.0f, 1.0f);
        
        IFCG::render();
        
        IFCG::swapBuffer();
    }

    IFCG::terminate();
    return 0;
}