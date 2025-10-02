#include <iostream>

#include "ifcg/ifcg.hpp"
#include "ifcg/graphics/mesh.hpp"
#include "ifcg/graphics/meshTree.hpp"
#include "ifcg/graphics/primitives/cube.hpp"

unsigned int width = 800;
unsigned int height = 600;

int main()
{
    IFCG::init(width, height, "Teste");
    IFCG::setup3D();

    auto* keys = IFCG::getInputHandler();
    auto* r = IFCG::getRenderer();

    auto* cube1 = new Cube(r->getShaderID());
    auto* cube2 = cube1->duplicate();
    cube2->translate(2.0f, 0.0f, 0.0f);
    auto* cube3 = cube1->duplicate();
    cube3->translate(-2.0f, 0.0f, 0.0f);

    keys->addKeyCallback(GLFW_KEY_UP, [&]() {
        if (keys->isKeyHeld(GLFW_KEY_UP))
            cube2->rotate(-0.01f, 1.0f, 0.0f, 0.0f);
    });
    keys->addKeyCallback(GLFW_KEY_DOWN, [&]() {
        if (keys->isKeyHeld(GLFW_KEY_DOWN))
            cube2->rotate(0.01f, 1.0f, 0.0f, 0.0f);
    });

    keys->addKeyCallback(GLFW_KEY_RIGHT, [&]() {
        if (keys->isKeyHeld(GLFW_KEY_RIGHT))
            cube3->rotate(-0.01f, 0.0f, 1.0f, 0.0f);
    });
    keys->addKeyCallback(GLFW_KEY_LEFT, [&]() {
        if (keys->isKeyHeld(GLFW_KEY_LEFT))
            cube3->rotate(0.01f, 0.0f, 1.0f, 0.0f);
    });

    auto* scene = new ifcg::MeshTree();
    scene->addChild(cube1);
    scene->addChild(cube2);
    scene->addChild(cube3);

    r->addMesh(scene);

    IFCG::setFramesPerSecond(120);
    IFCG::loop([&]() {});

    IFCG::terminate();
    return 0;
}