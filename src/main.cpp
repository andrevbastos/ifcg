#include <iostream>
#include <vector>
#include <thread>

#include "ifcg/ifcg.hpp"
#include "ifcg/graphics/mesh.hpp"
#include "ifcg/graphics/meshTree.hpp"
#include "ifcg/graphics/primitives/cube.hpp"
#include "ifcg/graphics/primitives/sphere.hpp"
#include "ifcg/graphics/primitives/pyramid.hpp"

int sequentialExample();
int parallelExample();

int main() {
    // Você pode escolher entre rodar o exemplo sequencial ou paralelo
    // return sequentialExample();
    return parallelExample();
}

using namespace ifcg;

int sequentialExample() {
    // 1. Inicialização e Janela
    Engine::init(800, 600, "IFCG Engine Showcase");
    Engine::setup3D();

    auto& input = Engine::getInputHandler();
    auto& renderer = Engine::getRenderer();
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
    input.addKeyCallback(Key::RIGHT, KeyAction::HELD, [solarSystem]() {
        solarSystem->rotate(0.02f, 0.0f, 1.0f, 0.0f);
    });
    input.addKeyCallback(Key::LEFT, KeyAction::HELD, [solarSystem]() {
        solarSystem->rotate(0.02f, 0.0f, -1.0f, 0.0f);
    });

    std::cout << "Engine Inicializada com sucesso!" << std::endl;
    std::cout << "Use as SETAS para rotacionar a cena." << std::endl;

    // 7. Loop Principal
    Engine::loop({
        .loopBody = [&]() {
            centralSphere->rotate(0.01f, 0.0f, 1.0f, 0.0f);
            leftPyramid->rotate(0.015f, 1.0f, 0.0f, 0.0f);
            
            rightCube->rotate(0.01f, 0.0f, 0.0f, 1.0f);
            satellite->rotate(0.05f, 0.0f, 1.0f, 0.0f);
        }
    });

    // 8. Limpeza segura de recursos
    Engine::terminate();
    return 0;
};

int parallelExample() {
    // 1. Inicialização e Janela
    Engine::init(800, 600, "IFCG Engine Showcase");
    Engine::setup3D();

    auto& input = Engine::getInputHandler();
    auto& renderer = Engine::getRenderer();
    GLuint shader = renderer.getShaderID();

    // 2. Criando objetos que pertencem à main/render thread
    auto centralSphere = std::make_shared<Sphere>(20, shader);
    centralSphere->setDrawMode(GL_LINE_LOOP);

    auto scene = std::make_shared<MeshTree>();
    scene->translate(0.0f, 0.0f, -10.0f);
    scene->addChild(centralSphere);

    std::shared_ptr<MeshBase> asyncMesh = nullptr;
    renderer.addMesh(scene);

    // 3. Geração assíncrona de dados em CPU
    Engine::runAsync([shader, scene, &asyncMesh]() {
        std::vector<Vertex> vertices {
            { -1.0f, -1.0f, 0.0f, 0.9f, 0.2f, 0.2f, 1.0f },
            {  1.0f, -1.0f, 0.0f, 0.2f, 0.9f, 0.2f, 1.0f },
            {  0.0f,  1.0f, 0.0f, 0.2f, 0.2f, 0.9f, 1.0f }
        };
        std::vector<GLuint> indices { 0, 1, 2 };

        // Criação de Mesh e alteração da cena acontecem obrigatoriamente na main thread.
        Engine::runOnMainThread([shader, scene, &asyncMesh, vertices = std::move(vertices), indices = std::move(indices)]() mutable {
            asyncMesh = std::make_shared<Mesh>(std::move(vertices), std::move(indices), shader);
            asyncMesh->translate(3.0f, 0.0f, 0.0f);
            scene->addChild(asyncMesh);
        });
    }, Priority::High);

    // 4. Callbacks de Input
    input.addKeyCallback(Key::RIGHT, KeyAction::HELD, [scene]() {
        scene->rotate(0.02f, 0.0f, 1.0f, 0.0f);
    });
    input.addKeyCallback(Key::LEFT, KeyAction::HELD, [scene]() {
        scene->rotate(0.02f, 0.0f, -1.0f, 0.0f);
    });
    
    // 5. Loop Principal: continua na main/render thread
    LoopConfig config {
        .mode = LoopMode::Concurrent,
        .loopBody = [&]() {
            centralSphere->rotate(0.01f, 0.0f, 1.0f, 0.0f);

            if (asyncMesh) {
                asyncMesh->rotate(0.02f, 0.0f, 0.0f, 1.0f);
            }
        }
    };

    std::cout << "Engine Inicializada com sucesso!" << std::endl;
    std::cout << "Use as SETAS para rotacionar a cena." << std::endl;

    Engine::loop(config);

    // 6. Limpeza segura de recursos
    Engine::terminate();
    
    return 0;
};