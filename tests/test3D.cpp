#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ifcg/ifcg.hpp"
#include "ifcg/graphics3D/scene/camera.hpp"
#include "ifcg/graphics3D/geometry/cube.hpp"
#include "ifcg/graphics3D/geometry/meshTree.hpp"

unsigned int width = 800;
unsigned int height = 600;

int main()
{
    IFCG::init();
    IFCG::createWindow(width, height);

    IFCG::setup3D();

    Cube3D* cube = new Cube3D(IFCG::shader.id);

    Mesh3D* wingHull = cube->duplicate();
    wingHull->scale(1.0f, 0.15f, 0.25f);

    Mesh3D* blades1 = cube->duplicate();
    blades1->scale(0.2f, 1.0f, 0.2f);
    blades1->rotate(0.5f, 0.0f, 1.0f, 0.0f);
    
    Mesh3D* blades2 = cube->duplicate();
    blades2->scale(1.0f, 0.2f, 0.2f);
    blades2->rotate(0.5f, 1.0f, 0.0f, 0.0f);

    MeshTree3D* propeller = new MeshTree3D({blades1, blades2});
    propeller->scale(0.3f, 0.3f, 0.3f);
    propeller->translate(0.0f, 0.0f, -1.0f);

    MeshTree3D* wing1 = new MeshTree3D({wingHull, propeller});
    wing1->translate(1.5f, 0.0f, 0.0f);

    MeshTree3D* wing2 = new MeshTree3D({wingHull, propeller});
    wing2->translate(-1.5f, 0.0f, 0.0f);

    IFCG::addMesh(wing1);
    IFCG::addMesh(wing2);
    
    float wingRot = 0;
    while (!IFCG::shouldClose())
    {
        IFCG::readInputs();
        IFCG::processInput();
        IFCG::clearBuffer(1.0f, 1.0f, 1.0f, 1.0f);
        
        if (glfwGetKey(IFCG::window, GLFW_KEY_UP) == GLFW_PRESS) {
            propeller->rotate(-0.1f, 0.0f, 0.0f, 1.0f);
        }
        if (glfwGetKey(IFCG::window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            if (wingRot <= 0.5f) {
                wingRot += 0.1f;
                wing1->rotate(0.1f, 1.0f, 0.0f, 0.0f);
                wing2->rotate(-0.1f, 1.0f, 0.0f, 0.0f);
            }
        } else if (glfwGetKey(IFCG::window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            if (wingRot >= -0.5f) {
                wingRot -= 0.1f;
                wing1->rotate(-0.1f, 1.0f, 0.0f, 0.0f);
                wing2->rotate(0.1f, 1.0f, 0.0f, 0.0f);
            }
        } else {
            if (wingRot > 0.01f) {
                wingRot -= 0.05f;
                wing1->rotate(-0.05f, 1.0f, 0.0f, 0.0f);
                wing2->rotate(0.05f, 1.0f, 0.0f, 0.0f);
            } else if (wingRot < -0.01f) {
                wingRot += 0.05f;
                wing1->rotate(0.05f, 1.0f, 0.0f, 0.0f);
                wing2->rotate(-0.05f, 1.0f, 0.0f, 0.0f);
            } else {
                wingRot = 0.0f;
            }
        }
        
        IFCG::render();
        
        IFCG::swapBuffer();
    }

    IFCG::terminate();
    return 0;
}