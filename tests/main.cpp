#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "ifcg.hpp"
#include "triangleMesh2D.hpp"

using namespace ifcg;
using namespace mesh2D;

unsigned int width = 800;
unsigned int height = 600;

int main()
{
    IFCG::init();
    IFCG::createWindow(width, height);

    Shader shaderProgram = IFCG::getDefaultShader2D();

    Triangle2D triangle(IFCG::getDefaultShader2D());

    while (!IFCG::shouldClose())
    {
        IFCG::processInput();
        IFCG::clearBuffer(1.0f, 1.0f, 1.0f, 1.0f);

        shaderProgram.activate();

        triangle.draw();

        IFCG::swapBuffer();
        IFCG::readInputs();
    }

    IFCG::terminate();
    return 0;
}