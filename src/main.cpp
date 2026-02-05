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

    auto* k = IFCG::getInputHandler();
    auto* r = IFCG::getRenderer();

    float xmount = 200.0f;
    float ymount = 200.0f;

    auto* cube1 = new Cube(r->getShaderID());
    cube1->translate(-(xmount/2), (ymount/2), 0.0f);

    auto* scene = new MeshTree();
    scene->translate(0.0f, 0.0f, -80.0f);
    for (int i = 0; i <= xmount; i += 2)
    {
        for (int j = 0; j <= ymount; j += 2)
        {
            auto* cube = cube1->duplicate();
            cube->translate(i, -j, 0.0f);
            scene->addChild(cube);

            k->addKeyCallback(GLFW_KEY_UP, [cube, k]() {
                if (k->isKeyHeld(GLFW_KEY_UP))
                    cube->rotate(0.01f, -1.0f, 0.0f, 0.0f);
            });
            k->addKeyCallback(GLFW_KEY_DOWN, [cube, k]() {
                if (k->isKeyHeld(GLFW_KEY_DOWN))
                    cube->rotate(0.01f, 1.0f, 0.0f, 0.0f);
            });

            k->addKeyCallback(GLFW_KEY_LEFT, [cube, k]() {
                if (k->isKeyHeld(GLFW_KEY_LEFT))
                    cube->rotate(0.01f, 0.0f, 1.0f, 0.0f);
            });
            k->addKeyCallback(GLFW_KEY_RIGHT, [cube, k]() {
                if (k->isKeyHeld(GLFW_KEY_RIGHT))
                    cube->rotate(-0.01f, 0.0f, 1.0f, 0.0f);
            });
        }
    }

    r->addMesh(scene);

    IFCG::setFramesPerSecond(120);
    IFCG::loop([&]() {});

    IFCG::terminate();
    return 0;
}