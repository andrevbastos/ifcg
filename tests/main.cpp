#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ifcg.hpp"
#include "3D/pyramidMesh3D.hpp"
#include "3D/cubeMesh3D.hpp"

using namespace ifcg;

unsigned int width = 800;
unsigned int height = 800;

int main()
{
    IFCG::init();
    IFCG::createWindow(width, height);

    Shader shader3D = IFCG::getDefaultShader3D();

    Pyramid3D pyramid(shader3D);
    pyramid.translate(0.5f, 0.5f, 0.0f);
    pyramid.scale(0.3f, 0.3f, 0.3f);

    Cube3D cube(shader3D);
    cube.translate(-0.5f, -0.5f, 0.0f);
    cube.scale(.3f, 0.3f, 0.3f);

    while (!IFCG::shouldClose())
    {
        IFCG::processInput();
        IFCG::clearBuffer(1.0f, 1.0f, 1.0f, 1.0f);

        shader3D.activate();

        pyramid.rotate(0.01f, glm::vec3(0.0f, 0.1f, 0.3f));
        pyramid.draw();

        cube.rotate(0.01f, glm::vec3(0.0f, 0.1f, 0.3f));
        cube.draw();

        IFCG::swapBuffer();
        IFCG::readInputs();
    }

    IFCG::terminate();
    return 0;
}