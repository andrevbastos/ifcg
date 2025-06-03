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

    Cube3D cube1(IFCG::shader.id);
    Cube3D cube2(IFCG::shader.id);
    Mesh3D cubes({&cube1, &cube2}, IFCG::shader.id);

    Pyramid3D pyramid(IFCG::shader.id);

    cube1.translate(2.0f, 0.0f, 1.0f);
    cube2.translate(-2.0f, 0.0f, 1.0f);

    pyramid.scale(0.5f, 0.5f, 0.5f);
    
    cubes.setOutline(true);
    pyramid.setOutline(true);

    IFCG::addMesh(&cubes);
    IFCG::addMesh(&pyramid);

    while (!IFCG::shouldClose())
    {
        IFCG::readInputs();
        IFCG::processInput();
        IFCG::clearBuffer(1.0f, 1.0f, 1.0f, 1.0f);

        cube1.rotate(0.1f, 1.0f, 0.0f, 0.0f);
        cube2.rotate(0.1f, 0.0f, 1.0f, 0.0f);
        cubes.rotate(0.05f, 0.0f, 0.0f, 1.0f);
        
        IFCG::render();
        
        IFCG::swapBuffer();
    }

    IFCG::terminate();
    return 0;
}