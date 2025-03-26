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
    Mesh cube(vertices, indices);
    
    // Variável de tempo para animação
    float time = 0.0f;

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

        // Matrizes de transformação
        glm::mat4 model = glm::mat4(1.0f);  // Matriz modelo (identidade)
        glm::mat4 view = glm::mat4(1.0f);   // Matriz de visualização (identidade)
        glm::mat4 proj = glm::mat4(1.0f);   // Matriz de projeção (identidade)

        // Atualiza o tempo para animação
        time += 0.01f;

        // Aplica transformações
        model = glm::rotate(model, time, glm::vec3(0.3f, 0.0f, 0.0f));  // Rotação nos eixos X, Y, Z
        view = glm::translate(view, glm::vec3(0.0f, -0.4f, -2.0f));     // Move a câmera nos eixos X, Y, Z
        proj = glm::perspective(glm::radians(45.0f), 
                (float)width / (float)height, 0.1f, 100.0f);            // Projeção de perspectiva

        // Passa as matrizes para os shaders
        GLuint modelLoc = glGetUniformLocation(shaderProgram._id, "model");
        GLuint viewLoc = glGetUniformLocation(shaderProgram._id, "view");
        GLuint projLoc = glGetUniformLocation(shaderProgram._id, "proj");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

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