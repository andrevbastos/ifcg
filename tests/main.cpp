#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ifcg.hpp"

// Configurações da janela
const GLuint width = 500;    // Largura da janela
const GLuint height = 500;   // Altura da janela

// Parâmetros para construção do cubo
// cx, cy, cz = centro do cubo
// l = metade da largura
float cx = 0.0f;  // Coordenada x do centro
float cy = 0.0f;  // Coordenada y do centro
float cz = 0.0f;  // Coordenada z do centro
float l = 0.2f;   // Metade do tamanho da aresta

// Definição dos vértices do cubo:
// Cada vértice contém posição (vec3) e cor (vec3)
std::vector<Vertex> vertices = {
    //        (layout = 0) aPos   (layout = 1) aColor
    // Vertex{glm::vec3(x, y, z), glm::vec3(R, G, B)},

    // Frente (azul)
    Vertex{glm::vec3(cx + l, cy + l, cz + l), glm::vec3(0.0f, 0.0f, 1.0f)},
    Vertex{glm::vec3(cx + l, cy - l, cz + l), glm::vec3(0.0f, 0.0f, 1.0f)},
    Vertex{glm::vec3(cx - l, cy - l, cz + l), glm::vec3(0.0f, 0.0f, 1.0f)},
    Vertex{glm::vec3(cx - l, cy + l, cz + l), glm::vec3(0.0f, 0.0f, 1.0f)},

    // Trás (vermelha)
    Vertex{glm::vec3(cx + l, cy + l, cz - l), glm::vec3(1.0f, 0.0f, 0.0f)},
    Vertex{glm::vec3(cx + l, cy - l, cz - l), glm::vec3(1.0f, 0.0f, 0.0f)},
    Vertex{glm::vec3(cx - l, cy - l, cz - l), glm::vec3(1.0f, 0.0f, 0.0f)},
    Vertex{glm::vec3(cx - l, cy + l, cz - l), glm::vec3(1.0f, 0.0f, 0.0f)},

    // Esquerda (verde)
    Vertex{glm::vec3(cx - l, cy + l, cz + l), glm::vec3(0.0f, 1.0f, 0.0f)},
    Vertex{glm::vec3(cx - l, cy - l, cz + l), glm::vec3(0.0f, 1.0f, 0.0f)},
    Vertex{glm::vec3(cx - l, cy - l, cz - l), glm::vec3(0.0f, 1.0f, 0.0f)},
    Vertex{glm::vec3(cx - l, cy + l, cz - l), glm::vec3(0.0f, 1.0f, 0.0f)},

    // Direita (amarela)
    Vertex{glm::vec3(cx + l, cy - l, cz + l), glm::vec3(1.0f, 1.0f, 0.0f)},
    Vertex{glm::vec3(cx + l, cy - l, cz - l), glm::vec3(1.0f, 1.0f, 0.0f)},
    Vertex{glm::vec3(cx + l, cy + l, cz - l), glm::vec3(1.0f, 1.0f, 0.0f)},
    Vertex{glm::vec3(cx + l, cy + l, cz + l), glm::vec3(1.0f, 1.0f, 0.0f)},

    // Cima (ciano)
    Vertex{glm::vec3(cx + l, cy + l, cz + l), glm::vec3(0.0f, 1.0f, 1.0f)},
    Vertex{glm::vec3(cx + l, cy + l, cz - l), glm::vec3(0.0f, 1.0f, 1.0f)},
    Vertex{glm::vec3(cx - l, cy + l, cz - l), glm::vec3(0.0f, 1.0f, 1.0f)},
    Vertex{glm::vec3(cx - l, cy + l, cz + l), glm::vec3(0.0f, 1.0f, 1.0f)},

    // Baixo (magenta)
    Vertex{glm::vec3(cx + l, cy - l, cz + l), glm::vec3(1.0f, 0.0f, 1.0f)},
    Vertex{glm::vec3(cx + l, cy - l, cz - l), glm::vec3(1.0f, 0.0f, 1.0f)},
    Vertex{glm::vec3(cx - l, cy - l, cz - l), glm::vec3(1.0f, 0.0f, 1.0f)},
    Vertex{glm::vec3(cx - l, cy - l, cz + l), glm::vec3(1.0f, 0.0f, 1.0f)}
};

// Índices para renderização
// Cada face é composta por 2 triângulos (6 vértices no total)
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

// Função para processar entrada do teclado
void processInput(GLFWwindow *window);

int main()
{
    // Inicialização do framework gráfico
    IFCG::init();

    // Configuração da janela e viewport
    IFCG::createWindow(width, height);
    IFCG::createViewport(width, height);
    GLFWwindow* window = IFCG::window;

    // Carregamento dos shaders
    Shader shaderProgram("../resources/shaders/default.vert", "../resources/shaders/default.frag");
    
    // Criação do mesh a partir dos vértices e índices
    Mesh cube(vertices, indices, shaderProgram._id);

    // Loop principal de renderização
    while (!glfwWindowShouldClose(window))
    {
        // Limpa o buffer de fundo branco e profundidade
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Processa eventos de entrada
        glfwPollEvents();
        processInput(window);

        // Ativa o programa de shader
        shaderProgram.activate();

        // Rotaciona cubo
        cube.rotate(0.01f, glm::vec3(0.0f, 0.3f, 0.1f));

        // Renderiza o cubo
        cube.draw();

        // Troca os buffers
        glfwSwapBuffers(window);
    }

    // Limpeza final
    shaderProgram.destroy();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

// Processa entrada do teclado - fecha a janela com ESC
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}