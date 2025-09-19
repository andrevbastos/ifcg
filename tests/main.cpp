#include <iostream>

#include "ifcg/ifcg.hpp"

unsigned int width = 800;
unsigned int height = 600;

int main()
{
    IFCG::init(width, height, "Teste");
    IFCG::setup3D();

    auto* keys = IFCG::getInputHandler();

    keys->addKeyCallback(GLFW_KEY_W, [&]() {
        if (keys->isKeyReleased(GLFW_KEY_W))
            std::cout << "W released!" << std::endl;
        if (keys->isKeyHeld(GLFW_KEY_W))
            std::cout << "W held!" << std::endl;
        if (keys->isKeyPressed(GLFW_KEY_W))
            std::cout << "W pressed!" << std::endl;
    });

    IFCG::setFramesPerSecond(120);
    IFCG::loop([&]() {});

    IFCG::terminate();
    return 0;
}