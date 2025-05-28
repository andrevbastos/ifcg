#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ifcg/ifcg.hpp"
#include "ifcg/graphics3D/scene/camera.hpp"
#include "ifcg/graphics3D/geometry/cube.hpp"

unsigned int width = 800;
unsigned int height = 600;

int main()
{
    IFCG::init();
    IFCG::createWindow(width, height);

    Shader shader3D = IFCG::getDefaultShader3D();

    Camera3D camera(width, height, glm::vec3(0.0f, 0.0f, 0.0f));

    Cube3D cube1(shader3D.id);
    Cube3D cube2(shader3D.id);
    Mesh3D cubes({&cube1, &cube2}, shader3D.id);

    cube1.translate(2.0f, 0.0f, 1.0f);
    cube2.translate(-2.0f, 0.0f, 1.0f);

    IFCG::addMesh(&cubes);

    while (!IFCG::shouldClose())
    {
        IFCG::readInputs();
        IFCG::processInput();
        IFCG::clearBuffer(1.0f, 1.0f, 1.0f, 1.0f);

        shader3D.activate();

        camera.inputs(IFCG::window);
        camera.update(90.0f, 0.1f, 100.0f, shader3D.id);

        cube1.rotate(0.1f, 1.0f, 0.0f, 0.0f);
        cube2.rotate(0.1f, 0.0f, 1.0f, 0.0f);
        cubes.rotate(0.05f, 0.0f, 0.0f, 1.0f);
        
        IFCG::render();
        
        IFCG::swapBuffer();
    }

    IFCG::terminate();
    return 0;
}