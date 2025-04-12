#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ifcg.hpp"
#include "2D/camera2D.hpp"
#include "2D/triangle_mesh2D.hpp"
#include "2D/square_mesh2D.hpp"
#include "2D/circle_mesh2D.hpp"

unsigned int width = 800;
unsigned int height = 600;

int main()
{
    IFCG::init();
    IFCG::createWindow(width, height);

    Shader shader2D = IFCG::getDefaultShader2D();

    Camera2D camera(width, height, glm::vec3(0.0f, 0.0f, 5.0f));

    Triangle2D triangle(shader2D);
    Square2D square(shader2D);
    Circle2D circle(100, shader2D);

    while (!IFCG::shouldClose())
    {
        IFCG::processInput();
        IFCG::clearBuffer(1.0f, 1.0f, 1.0f, 1.0f);
        
        shader2D.activate();
        
        camera.inputs(IFCG::window);
        camera.update(45.0f, 0.1f, 100.0f, shader2D);

        triangle.draw();

        IFCG::swapBuffer();
        IFCG::readInputs();
    }

    IFCG::terminate();
    return 0;
}