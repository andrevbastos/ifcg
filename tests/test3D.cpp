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

    Cube3D wingHull(IFCG::shader.id);
    wingHull.scale(1.0f, 0.15f, 0.25f);

    Cube3D blades1(IFCG::shader.id);
    blades1.scale(glm::vec3(0.2f, 1.0f, 0.2f));
    Cube3D blades2(IFCG::shader.id);
    blades2.scale(glm::vec3(1.0f, 0.2f, 0.2f));

    Mesh3D propeller({&blades1, &blades2}, IFCG::shader.id);
    propeller.scale(0.3f, 0.3f, 0.3f);
    propeller.translate(0.0f, 0.0f, -1.0f);

    Mesh3D wing1({&wingHull, &propeller}, IFCG::shader.id);
    wing1.translate(1.5f, 0.0f, 0.0f);
    wing1.setOutline(true);

    Mesh3D wing2({&wingHull, &propeller}, IFCG::shader.id);
    wing2.translate(-1.5f, 0.0f, 0.0f);
    wing2.reflect(true, false, false);
    wing2.setOutline(true);

    IFCG::addMesh(&wing1);
    IFCG::addMesh(&wing2);
    
    float wingRot = 0;
    while (!IFCG::shouldClose())
    {
        IFCG::readInputs();
        IFCG::processInput();
        IFCG::clearBuffer(1.0f, 1.0f, 1.0f, 1.0f);

        propeller.rotate(-0.1f, glm::vec3(0.0f, 0.0f, 1.0f));

        if (glfwGetKey(IFCG::window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            if (wingRot <= 0.5f) {
                wingRot += 0.1f;
                wing1.rotate(0.1f, glm::vec3(1.0f, 0.0f, 0.0f));
                wing2.rotate(-0.1f, glm::vec3(1.0f, 0.0f, 0.0f));
            }
        } else if (glfwGetKey(IFCG::window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            if (wingRot >= -0.5f) {
                wingRot -= 0.1f;
                wing1.rotate(-0.1f, glm::vec3(1.0f, 0.0f, 0.0f));
                wing2.rotate(0.1f, glm::vec3(1.0f, 0.0f, 0.0f));
            }
        } else {
            if (wingRot > 0.05f) {
                wingRot -= 0.05f;
                wing1.rotate(-0.05f, glm::vec3(1.0f, 0.0f, 0.0f));
                wing2.rotate(0.05f, glm::vec3(1.0f, 0.0f, 0.0f));
            } else if (wingRot < -0.05f) {
                wingRot += 0.05f;
                wing1.rotate(0.05f, glm::vec3(1.0f, 0.0f, 0.0f));
                wing2.rotate(-0.05f, glm::vec3(1.0f, 0.0f, 0.0f));
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