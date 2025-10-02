#include <iostream>

#include "ifcg/ifcg.hpp"
#include "ifcg/graphics/meshTree.hpp"
#include "ifcg/graphics/primitives/circle.hpp"
#include "ifcg/graphics/primitives/cube.hpp"
#include "ifcg/graphics/primitives/pyramid.hpp"
#include "ifcg/graphics/primitives/sphere.hpp"
#include "ifcg/graphics/primitives/square.hpp"
#include "ifcg/graphics/primitives/triangle.hpp"

unsigned int width = 800;
unsigned int height = 600;

int main()
{
    IFCG::init(width, height, "Teste");
    IFCG::setup3D();

    auto* keys = IFCG::getInputHandler();
    auto* r = IFCG::getRenderer();

    auto* cube = new Cube(r->getShaderID());

    keys->addKeyCallback(GLFW_KEY_UP, [&]() {
        if (keys->isKeyHeld(GLFW_KEY_UP))
            cube->rotate(-0.01f, 1.0f, 0.0f, 0.0f);
    });
    keys->addKeyCallback(GLFW_KEY_DOWN, [&]() {
        if (keys->isKeyHeld(GLFW_KEY_DOWN))
            cube->rotate(0.01f, 1.0f, 0.0f, 0.0f);
    });

    r->addMesh(cube);

    IFCG::setFramesPerSecond(120);
    IFCG::loop([&]() {});

    IFCG::terminate();
    return 0;
}