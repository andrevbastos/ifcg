#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ifcg/ifcg.hpp"
#include "ifcg/graphics3D/scene/camera.hpp"
#include "ifcg/graphics3D/geometry/cube.hpp"
#include "ifcg/graphics3D/geometry/pyramid.hpp"

unsigned int width = 800;
unsigned int height = 600;

int main()
{
    IFCG::init();
    IFCG::createWindow(width, height);

    IFCG::setup3D();

    Cube3D cube(IFCG::shader.id);

    IFCG::addMesh(&cube);

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