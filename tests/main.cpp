#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ifcg.hpp"

const GLuint width = 500;    // Largura da janela
const GLuint height = 500;   // Altura da janela

int main()
{
    IFCG::init();
    IFCG::createWindow(width, height);
    IFCG::createViewport(width, height);
    GLFWwindow* window = IFCG::window;

    Shader shaderProgram("../resources/shaders/default.vert", "../resources/shaders/default.frag");
    
    Mesh cube(IFCG::cubeVertex(), IFCG::cubeIndex(), shaderProgram._id);
    cube.scale(0.2, 0.2, 0.2); 

    Mesh pyramid(IFCG::pyramidVertex(), IFCG::pyramidIndex(), shaderProgram._id);
    pyramid.scale(0.3, 0.3, 0.3); 

    std::vector<Mesh> testeVector = { cube, pyramid };
    Mesh testeMesh(testeVector, shaderProgram._id);

    float time = 0.0f;
    while (!glfwWindowShouldClose(window))
    {   
        IFCG::clearBuffer();
        IFCG::readInputs(window);

        shaderProgram.activate();

        // cube.rotate(0.01f, glm::vec3(0.0f, 0.3f, 0.0f));
        // cube.draw();

        // pyramid.rotate(0.01f, glm::vec3(0.0f, 0.3f, 0.0f));
        // pyramid.draw();

        testeMesh.rotate(0.01f, glm::vec3(0.3f, 0.3f, 0.3f));
        testeMesh.draw();

        glfwSwapBuffers(window);
    }

    shaderProgram.destroy();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}