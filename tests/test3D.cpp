#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ifcg.hpp"
#include "3D/camera3D.hpp"
#include "3D/pyramid_mesh3D.hpp"
#include "3D/cube_mesh3D.hpp"

unsigned int width = 800;
unsigned int height = 600;

int main()
{
    IFCG::init();
    IFCG::createWindow(width, height);

    Shader shader3D = IFCG::getDefaultShader3D();

    Camera3D camera(width, height, glm::vec3(0.0f, 0.0f, -2.0f));

    Mesh3D floor({
            Vertex3D( 1.0f, -1.0f,  1.0f, 0.5f, 0.5f, 0.5f),
            Vertex3D( 1.0f, -1.0f, -1.0f, 0.5f, 0.5f, 0.5f),
            Vertex3D(-1.0f, -1.0f, -1.0f, 0.5f, 0.5f, 0.5f),
            Vertex3D(-1.0f, -1.0f,  1.0f, 0.5f, 0.5f, 0.5f),
        },{
            0, 1, 3,
            1, 2, 3
        },
        shader3D._id
    );

    Pyramid3D pyramid(shader3D);
    pyramid.translate(0.5f, 0.5f, 0.0f);
    pyramid.scale(0.3f, 0.3f, 0.3f);

    Cube3D cube(shader3D);
    cube.translate(-0.5f, -0.5f, 0.0f);
    cube.scale(0.3f, 0.3f, 0.3f);

    while (!IFCG::shouldClose())
    {
        IFCG::processInput();
        IFCG::clearBuffer(1.0f, 1.0f, 1.0f, 1.0f);

        shader3D.activate();

        camera.inputs(IFCG::window);
        camera.update(45.0f, 0.1f, 100.0f, shader3D);

        pyramid.rotate(0.01f, glm::vec3(0.0f, 0.1f, 0.3f));
        pyramid.draw();

        cube.rotate(0.01f, glm::vec3(0.0f, 0.1f, 0.3f));
        cube.draw();

        floor.draw();

        IFCG::swapBuffer();
        IFCG::readInputs();
    }

    IFCG::terminate();
    return 0;
}