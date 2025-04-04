#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "ifcg.hpp"
#include "triangleMesh2D.hpp"
#include "squareMesh2D.hpp"

using namespace ifcg;
using namespace mesh2D;

unsigned int width = 800;
unsigned int height = 800;

int main()
{
    IFCG::init();
    IFCG::createWindow(width, height);

    Shader shaderProgram = IFCG::getDefaultShader2D();

    Triangle2D triangle(IFCG::getDefaultShader2D());
    triangle.translate(-0.5f, -0.5f);
    triangle.scale(0.5f, 0.5f);

    Square2D square(shaderProgram);
    square.translate(0.5f, 0.5f);
    square.scale(0.5f, 0.5f);

    while (!IFCG::shouldClose())
    {
        IFCG::processInput();
        IFCG::clearBuffer(1.0f, 1.0f, 1.0f, 1.0f);

        shaderProgram.activate();

        triangle.rotate(0.01f);
        triangle.draw();

        square.rotate(0.01f);
        square.draw();

        IFCG::swapBuffer();
        IFCG::readInputs();
    }

    IFCG::terminate();
    return 0;
}