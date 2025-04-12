#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ifcg.hpp"
#include "2D/camera2D.hpp"
#include "2D/square_mesh2D.hpp"
#include "2D/triangle_mesh2D.hpp"

unsigned int width = 800;
unsigned int height = 600;

int main()
{
    IFCG::init();
    IFCG::createWindow(width, height);

    Shader shader2D = IFCG::getDefaultShader2D();

    Camera2D camera(width, height, glm::vec3(0.0f, 0.0f, 5.0f));

    Mesh2D background({
            Vertex2D( 1.0f, -1.0f, 0.5f, 0.5f, 0.5f),
            Vertex2D( 1.0f, -1.0f, 0.5f, 0.5f, 0.5f),
            Vertex2D(-1.0f, -1.0f, 0.5f, 0.5f, 0.5f),
            Vertex2D(-1.0f, -1.0f, 0.5f, 0.5f, 0.5f),
        },{
            0, 1, 3,
            1, 2, 3
        },
        shader2D._id
    );

    Triangle2D triangle(shader2D);
    triangle.translate(0.5f, 0.5f);
    triangle.scale(0.3f, 0.3f);

    Square2D square(shader2D);
    square.translate(-0.5f, -0.5f);
    square.scale(0.3f, 0.3f);

    while (!IFCG::shouldClose())
    {
        IFCG::processInput();
        IFCG::clearBuffer(1.0f, 1.0f, 1.0f, 1.0f);
        
        shader2D.activate();
        
        camera.inputs(IFCG::window);
        camera.update(45.0f, 0.1f, 100.0f, shader2D);

        triangle.rotate(0.01f);
        triangle.draw();
        
        square.rotate(0.01f);
        square.draw();

        background.draw();
        
        IFCG::swapBuffer();
        IFCG::readInputs();
    }

    IFCG::terminate();
    return 0;
}