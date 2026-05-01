#include <iostream>
#include <vector>
#include <thread>

#include "ifcg/ifcg.hpp"
#include "ifcg/graphics/mesh.hpp"
#include "ifcg/graphics/meshTree.hpp"
#include "ifcg/graphics/primitives/cube.hpp"
#include "ifcg/graphics/primitives/sphere.hpp"
#include "ifcg/graphics/primitives/pyramid.hpp"

using namespace ifcg;

int sequentialExample();
int parallelExample();

int main() 
{
    // return sequentialExample();
    return parallelExample();
}

int sequentialExample() {
    // 1. Inicialização e Janela
    IFCG::init(800, 600, "IFCG Engine Showcase");
    IFCG::setup3D();

    auto& input = IFCG::getInputHandler();
    auto& renderer = IFCG::getRenderer();
    GLuint shader = renderer.getShaderID();

    // 2. Criando Primitivas (Agora com make_shared)
    auto centralSphere = std::make_shared<Sphere>(20, shader);
    centralSphere->setDrawMode(GL_LINE_LOOP);
    auto leftPyramid = std::make_shared<Pyramid>(shader);
    auto rightCube = std::make_shared<Cube>(shader);

    // 3. Configurando a Hierarquia (MeshTree)
    auto solarSystem = std::make_shared<MeshTree>();
    solarSystem->translate(0.0f, 0.0f, -10.0f); // Afasta a câmera

    // A esfera será o centro
    solarSystem->addChild(centralSphere);

    // Adiciona outros objetos como filhos
    leftPyramid->translate(-4.0f, 0.0f, 0.0f);
    solarSystem->addChild(leftPyramid);

    rightCube->translate(4.0f, 0.0f, 0.0f);

    // 4. Demonstração de Duplicação e Estilo (Outline)
    // O método duplicate() já retorna std::shared_ptr<MeshBase>
    auto satellite = rightCube->duplicate();
    satellite->translate(0.0f, 2.0f, 0.0f);
    satellite->scale(0.4f, 0.4f, 0.4f);
    
    auto cubeWithSattelite = std::make_shared<MeshTree>();
    cubeWithSattelite->addChild(rightCube);
    cubeWithSattelite->addChild(satellite);
    solarSystem->addChild(cubeWithSattelite);

    // 5. Adicionando à fila de renderização
    renderer.addMesh(solarSystem);

    // 6. Callbacks de Input
    // Capturamos por valor '=' para o lambda lidar bem com o shared_ptr internamente
    input.addKeyCallback(GLFW_KEY_RIGHT, [solarSystem, &input]() {
        if (input.isKeyHeld(GLFW_KEY_RIGHT)) solarSystem->rotate(0.02f, 0.0f, 1.0f, 0.0f);
    });
    input.addKeyCallback(GLFW_KEY_LEFT, [solarSystem, &input]() {
        if (input.isKeyHeld(GLFW_KEY_LEFT)) solarSystem->rotate(0.02f, 0.0f, -1.0f, 0.0f);
    });

    std::cout << "IFCG Inicializada com sucesso!" << std::endl;
    std::cout << "Use as SETAS para rotacionar a cena." << std::endl;

    // 7. Loop Principal
    IFCG::loop({
        .loopBody = [&]() {
            centralSphere->rotate(0.01f, 0.0f, 1.0f, 0.0f);
            leftPyramid->rotate(0.015f, 1.0f, 0.0f, 0.0f);
            
            rightCube->rotate(0.01f, 0.0f, 0.0f, 1.0f);
            satellite->rotate(0.05f, 0.0f, 1.0f, 0.0f);
        }
    });

    // 8. Limpeza segura de recursos
    IFCG::terminate();
    return 0;
};

int parallelExample() {
    // 1. Inicialização e Janela
    IFCG::init(800, 600, "IFCG Engine Showcase");
    IFCG::setup3D();

    auto& input = IFCG::getInputHandler();
    auto& renderer = IFCG::getRenderer();
    GLuint shader = renderer.getShaderID();

    // 2. Criando Primitivas
    auto centralSphere = std::make_shared<Sphere>(20, shader);
    centralSphere->setDrawMode(GL_LINE_LOOP);
    auto leftPyramid = std::make_shared<Pyramid>(shader);
    auto rightCube = std::make_shared<Cube>(shader);

    // 3. Configurando a Hierarquia (MeshTree)
    auto solarSystem = std::make_shared<MeshTree>();
    solarSystem->translate(0.0f, 0.0f, -10.0f); 

    solarSystem->addChild(centralSphere);

    leftPyramid->translate(-4.0f, 0.0f, 0.0f);
    solarSystem->addChild(leftPyramid);

    rightCube->translate(4.0f, 0.0f, 0.0f);

    // 4. Demonstração de Duplicação e Estilo (Outline)
    auto satellite = rightCube->duplicate();
    satellite->translate(0.0f, 2.0f, 0.0f);
    satellite->scale(0.4f, 0.4f, 0.4f);
    
    auto cubeWithSattelite = std::make_shared<MeshTree>();
    cubeWithSattelite->addChild(rightCube);
    cubeWithSattelite->addChild(satellite);
    solarSystem->addChild(cubeWithSattelite);

    // 5. Adicionando à fila de renderização
    renderer.addMesh(solarSystem);

    // 6. Callbacks de Input
    input.addKeyCallback(GLFW_KEY_RIGHT, [solarSystem, &input]() {
        if (input.isKeyHeld(GLFW_KEY_RIGHT)) solarSystem->rotate(0.02f, 0.0f, 1.0f, 0.0f);
    });
    input.addKeyCallback(GLFW_KEY_LEFT, [solarSystem, &input]() {
        if (input.isKeyHeld(GLFW_KEY_LEFT)) solarSystem->rotate(0.02f, 0.0f, -1.0f, 0.0f);
    });
    
    // 7. Loop Principal em Paralelo
    LoopConfig config {
        .loopBody = [&]() {
            centralSphere->rotate(0.01f, 0.0f, 1.0f, 0.0f);
            leftPyramid->rotate(0.015f, 1.0f, 0.0f, 0.0f);
            rightCube->rotate(0.01f, 0.0f, 0.0f, 1.0f);
            satellite->rotate(0.05f, 0.0f, 1.0f, 0.0f);
        }
    };

    std::cout << "IFCG Inicializada com sucesso!" << std::endl;
    std::cout << "Renderizando em SEGUNDO PLANO!" << std::endl;

    IFCG::releaseContext();

    std::jthread loopThread(IFCG::loopP, config);

    while (IFCG::isRunning()) {
        IFCG::pollEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    loopThread.request_stop();
    loopThread.join();

    // 8. Limpeza segura de recursos
    IFCG::terminate();
    
    return 0;
};