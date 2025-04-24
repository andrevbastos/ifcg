#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ifcg.hpp"
#include "3D/mesh3D.hpp"
#include "3D/camera3D.hpp"
#include "3D/cube_mesh3D.hpp"
#include "3D/pyramid_mesh3D.hpp"
#include "3D/sphere_mesh3D.hpp"

unsigned int width = 800;
unsigned int height = 600;

int main()
{
    IFCG::init();
    IFCG::createWindow(width, height);

    Shader shader3D = IFCG::getDefaultShader3D();

    Camera3D camera(width, height, glm::vec3(0.0f, 0.0f, 0.0f));

    Cube3D cube(shader3D.id);

    while (!IFCG::shouldClose())
    {
        IFCG::readInputs();
        IFCG::processInput();
        IFCG::clearBuffer(1.0f, 1.0f, 1.0f, 1.0f);

        shader3D.activate();

        camera.inputs(IFCG::window);
        camera.update(90.0f, 0.1f, 100.0f, shader3D.id);
        
        cube.draw();

        IFCG::swapBuffer();
    }

    IFCG::terminate();
    return 0;
}