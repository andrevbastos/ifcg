#include <filesystem>
#include <iostream>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "ebo.hpp"
#include "shader.hpp"
#include "vao.hpp"
#include "vbo.hpp"

std::string path(const std::string &filepath) {
    std::string path = std::filesystem::absolute(PROJECT_ROOT_FOLDER);
    // join the path with the file
    path = path + "/" + filepath;
    return path;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

float vertices[] = {
    // positions        // colors
    0.5f,  0.5f,  0.0f, 0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f};

GLuint indices[] = {0, 1, 3, 1, 2, 3};

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, 500, 500);

    Shader shaderProgram(path("resources/shaders/default_vert.glsl").c_str(),
                         path("resources/shaders/default_frag.glsl").c_str());

    VAO vao;
    vao.bind();

    VBO vbo(sizeof(vertices), vertices);
    EBO ebo(sizeof(indices), indices);

    vao.linkAttrib(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void *)0);
    vao.linkAttrib(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float),
                   (void *)(3 * sizeof(float)));
    vao.unbind();
    vbo.unbind();
    ebo.unbind();

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Close window
        glfwPollEvents();
        processInput(window);

        shaderProgram.activate();
        vao.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
    }

    vao.destroy();
    vbo.destroy();
    ebo.destroy();
    shaderProgram.destroy();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
