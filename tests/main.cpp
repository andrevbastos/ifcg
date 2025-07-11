#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ifcg/ifcg.hpp"
#include "ifcg/common/mesh.hpp"
#include "ifcg/graphics3D/geometry/meshTree.hpp"
#include "ifcg/graphics3D/geometry/cube.hpp"

unsigned int width = 800;
unsigned int height = 600;

int main()
{
    IFCG::init();
    IFCG::createWindow(width, height);

    IFCG::setup3D();

    // Criação de 1 cubo
    Cube3D* cube1 = new Cube3D(IFCG::shader.id);
    cube1->translate(0.0f, 0.0f, -5.0f);

    // Duplicação do cubo em outros 2
    Mesh3D* cube2 = cube1->duplicate();
    cube2->translate(3.0f, 0.0f, 0.0f);
    Mesh3D* cube3 = cube1->duplicate();
    cube3->translate(-3.0f, 0.0f, 0.0f);

    // Criação de uma árvore com 2 cubos e adição exterior de um terceiro
    MeshTree3D* meshTree = new MeshTree3D({cube1, cube2});
    meshTree->addSubMesh(cube3);
    
    // Duplicação da árvore
    MeshTree3D* meshTree2 = meshTree->duplicate();
    meshTree2->translate(0.0f, 3.0f, 0.0f);

    // Outline para diferenciar as árvores
    meshTree2->setOutline(true);

    // Recuperar uma malha da árvore duplicada
    auto* cube1Copy = meshTree2->getSubMesh(0);
    
    // Adiciona as árvores há fila de renderização
    IFCG::addMesh(meshTree);
    IFCG::addMesh(meshTree2);

    IFCG::setFramesPerSecond(120);
    IFCG::loop([&]() 
    {   
        cube2->rotate(0.01f, 0.0f, 1.0f, 0.0f);
        cube3->rotate(0.01f, 0.0f, 0.0f, 1.0f);   

        cube1Copy->rotate(0.01f, 1.0f, 0.0f, 0.0f);
     });

    IFCG::terminate();
    return 0;
}