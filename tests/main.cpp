#include <filesystem>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// #include "shader.hpp"
// #include "mesh.hpp"
#include "ifcg.hpp"

const GLuint width = 500;
const GLuint height = 500;

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    IFCG::init();

    IFCG::createWindow(width, height);
    IFCG::createViewport(width, height);
    GLFWwindow* window = IFCG::window;

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Close window
        glfwPollEvents();
        processInput(window);

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
