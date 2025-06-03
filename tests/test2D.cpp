#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ifcg/ifcg.hpp"
#include "ifcg/graphics2D/scene/camera.hpp"
#include "ifcg/graphics2D/geometry/square.hpp"
#include "ifcg/graphics2D/geometry/triangle.hpp"

unsigned int width = 800;
unsigned int height = 600;

int main()
{
    IFCG::init();
    IFCG::createWindow(width, height);

    IFCG::setup2D();

    Square2D square1(IFCG::shader.id);
    Square2D square2(IFCG::shader.id);
    Mesh2D squares({&square1, &square2}, IFCG::shader.id);

    Triangle2D triangle(IFCG::shader.id);

    square1.translate(2.0f, 0.0f);
    square2.translate(-2.0f, 0.0f);

    triangle.scale(0.5f, 0.5f);

    IFCG::addMesh(&squares);
    IFCG::addMesh(&triangle);

    while (!IFCG::shouldClose())
    {
        IFCG::readInputs();
        IFCG::processInput();
        IFCG::clearBuffer(1.0f, 1.0f, 1.0f, 1.0f);
    
        square1.rotate(0.1f);
        square2.rotate(0.1f);
        squares.rotate(0.05f);

        IFCG::render();
        
        IFCG::swapBuffer();
    }

    IFCG::terminate();
    return 0;
}