#include <iostream>
#include <vector>

#include "ifcg/ifcg.hpp"
#include "ifcg/graphics/mesh.hpp"
#include "ifcg/graphics/meshTree.hpp"
#include "ifcg/graphics/primitives/cube.hpp"
#include "ifcg/graphics/primitives/sphere.hpp"
#include "ifcg/graphics/primitives/pyramid.hpp"

using namespace ifcg;

int main() 
{
    // 1. Inicialização e Janela
    IFCG::init(800, 600, "IFCG Engine Showcase");
    IFCG::setup3D();

    auto* input = IFCG::getInputHandler();
    auto* renderer = IFCG::getRenderer();
    GLuint shader = renderer->getShaderID();

    // 2. Criando Primitivas
    auto* centralSphere = new Sphere(20, shader);
    auto* leftPyramid = new Pyramid(shader);
    auto* rightCube = new Cube(shader);

    // 3. Configurando a Hierarquia (MeshTree)
    // Vamos criar um "Sistema Solar" simplificado
    auto* solarSystem = new MeshTree();
    solarSystem->translate(0.0f, 0.0f, -10.0f); // Afasta a câmera

    // A esfera será o centro
    solarSystem->addChild(centralSphere);

    // Adiciona outros objetos como filhos (eles herdam a translação do solarSystem)
    leftPyramid->translate(-4.0f, 0.0f, 0.0f);
    solarSystem->addChild(leftPyramid);

    rightCube->translate(4.0f, 0.0f, 0.0f);

    // 4. Demonstração de Duplicação e Estilo (Outline)
    // Duplicamos o cubo para criar um "satélite"
    auto* satellite = rightCube->duplicate();
    satellite->translate(0.0f, 2.0f, 0.0f);
    satellite->scale(0.4f, 0.4f, 0.4f);
    auto* cubeWithSattelite = new MeshTree();
    cubeWithSattelite->addChild(rightCube);
    cubeWithSattelite->addChild(satellite);
    solarSystem->addChild(cubeWithSattelite);

    // 5. Adicionando à fila de renderização
    renderer->addMesh(solarSystem);

    // 6. Callbacks de Input (Estilo Nomai/Interativo)
    // Controlar a rotação do sistema inteiro com as setas
    input->addKeyCallback(GLFW_KEY_RIGHT, [solarSystem, input]() {
        if (input->isKeyHeld(GLFW_KEY_RIGHT)) solarSystem->rotate(0.02f, 0.0f, 1.0f, 0.0f);
    });
    input->addKeyCallback(GLFW_KEY_LEFT, [solarSystem, input]() {
        if (input->isKeyHeld(GLFW_KEY_LEFT)) solarSystem->rotate(0.02f, 0.0f, -1.0f, 0.0f);
    });

    std::cout << "IFCG Inicializada com sucesso!" << std::endl;
    std::cout << "Use as SETAS para rotacionar a cena." << std::endl;

    // 7. Loop Principal
    IFCG::loop([&]() {
        // Animações automáticas constantes
        centralSphere->rotate(0.01f, 0.0f, 1.0f, 0.0f);
        leftPyramid->rotate(0.015f, 1.0f, 0.0f, 0.0f);
        
        // O satélite gira em torno do cubo, que por sua vez está no sistema
        rightCube->rotate(0.01f, 0.0f, 0.0f, 1.0f);
        satellite->rotate(0.05f, 0.0f, 1.0f, 0.0f);
    });

    // 8. Limpeza segura de recursos
    IFCG::terminate();
    return 0;
}