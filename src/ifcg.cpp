#include "ifcg.hpp"
#include <iostream>

IFCG* IFCG::instance = nullptr;
GLFWwindow* IFCG::window = nullptr;

IFCG::IFCG()
{
    glfwInit();
}

IFCG* IFCG::init()
{
    if (instance == nullptr)
    {
        instance = new IFCG();
        window = NULL;
    }
    return instance;
}

void IFCG::createWindow(GLuint width, GLuint height)
{
    if (window == nullptr)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);

        if (window == nullptr)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }
    }

    glfwMakeContextCurrent(window);
}

void IFCG::createViewport(GLuint width, GLuint height)
{
	gladLoadGL();
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
}

void IFCG::clearBuffer()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
};

void IFCG::readInputs(GLFWwindow* window)
{
    glfwPollEvents();
    processInput(window);
};

void IFCG::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

std::vector<Vertex> IFCG::cubeVertex()
{
    std::vector<Vertex> vertices = {
        //        (layout = 0) aPos   (layout = 1) aColor
        // Vertex{glm::vec3(x, y, z), glm::vec3(R, G, B)},

        // Frente (azul)
        Vertex{glm::vec3(+1.0f, +1.0f, +1.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
        Vertex{glm::vec3(+1.0f, -1.0f, +1.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
        Vertex{glm::vec3(-1.0f, -1.0f, +1.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
        Vertex{glm::vec3(-1.0f, +1.0f, +1.0f), glm::vec3(0.0f, 0.0f, 1.0f)},

        // Trás (vermelha)
        Vertex{glm::vec3(+1.0f, +1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
        Vertex{glm::vec3(+1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
        Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
        Vertex{glm::vec3(-1.0f, +1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f)},

        // Esquerda (verde)
        Vertex{glm::vec3(-1.0f, +1.0f, +1.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
        Vertex{glm::vec3(-1.0f, -1.0f, +1.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
        Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
        Vertex{glm::vec3(-1.0f, +1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f)},

        // Direita (amarela)
        Vertex{glm::vec3(+1.0f, -1.0f, +1.0f), glm::vec3(1.0f, 1.0f, 0.0f)},
        Vertex{glm::vec3(+1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f)},
        Vertex{glm::vec3(+1.0f, +1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f)},
        Vertex{glm::vec3(+1.0f, +1.0f, +1.0f), glm::vec3(1.0f, 1.0f, 0.0f)},

        // Cima (ciano)
        Vertex{glm::vec3(+1.0f, +1.0f, +1.0f), glm::vec3(0.0f, 1.0f, 1.0f)},
        Vertex{glm::vec3(+1.0f, +1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f)},
        Vertex{glm::vec3(-1.0f, +1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f)},
        Vertex{glm::vec3(-1.0f, +1.0f, +1.0f), glm::vec3(0.0f, 1.0f, 1.0f)},

        // Baixo (magenta)
        Vertex{glm::vec3(+1.0f, -1.0f, +1.0f), glm::vec3(1.0f, 0.0f, 1.0f)},
        Vertex{glm::vec3(+1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f)},
        Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f)},
        Vertex{glm::vec3(-1.0f, -1.0f, +1.0f), glm::vec3(1.0f, 0.0f, 1.0f)}
    };

    return vertices;
};

std::vector<GLuint> IFCG::cubeIndex() {
    std::vector<GLuint> indices = {
        // Frente
        0, 1, 3,  // Primeiro triângulo
        1, 2, 3,  // Segundo triângulo

        // Trás
        4, 5, 7,
        5, 6, 7,

        // Esquerda
        8, 9, 11,
        9, 10, 11,

        // Direita
        12, 13, 15,
        13, 14, 15,

        // Cima
        16, 17, 19,
        17, 18, 19,

        // Baixo
        20, 21, 23,
        21, 22, 23
    };
    return indices;
};

std::vector<Vertex> IFCG::pyramidVertex()
{
    std::vector<Vertex> vertices = {       
        //        (layout = 0) aPos   (layout = 1) aColor
        // Vertex{glm::vec3(x, y, z), glm::vec3(R, G, B)}
        // Base (magenta)
        Vertex{glm::vec3(+1.0f, -1.0f, +1.0f), glm::vec3(1.0f, 0.0f, 1.0f)},
        Vertex{glm::vec3(+1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f)},
        Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f)},
        Vertex{glm::vec3(-1.0f, -1.0f, +1.0f), glm::vec3(1.0f, 0.0f, 1.0f)},

        // Frente (azul)
        Vertex{glm::vec3(-1.0f, -1.0f, +1.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
        Vertex{glm::vec3(+1.0f, -1.0f, +1.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
        Vertex{glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)},

        // Direita (amarela)
        Vertex{glm::vec3(+1.0f, -1.0f, +1.0f), glm::vec3(1.0f, 1.0f, 0.0f)},
        Vertex{glm::vec3(+1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f)},
        Vertex{glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f)},

        // Trás (vermelha)
        Vertex{glm::vec3(+1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
        Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
        Vertex{glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},

        // Esquerda (verde)
        Vertex{glm::vec3(-1.0f, -1.0f, +1.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
        Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
        Vertex{glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)}
    };
    return vertices;
};

std::vector<GLuint> IFCG::pyramidIndex() {
    std::vector<GLuint> indices = {
        // Baixo
        0, 1, 3,
        1, 2, 3,

        // Frente
        4, 5, 6,

        // Direita
        7, 8, 9,

        // Trás
        10, 11, 12,

        // Esquerda
        13, 14, 15
    };
    return indices;
};
