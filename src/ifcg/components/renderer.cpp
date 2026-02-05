#include "ifcg/components/renderer.hpp"

namespace ifcg
{
    Renderer::Renderer(Window* win)
        : _renderQueue({}), _window(win) {
        _shader = nullptr;
        _camera = nullptr;
    };

    void Renderer::setup2D() {
        _shader = new Shader("../resources/shaders/default2D_vert.glsl", "../resources/shaders/default2D_frag.glsl");
        _camera = new Camera2D(_window->getWidth(), _window->getHeight());
        _camera->setPos(glm::vec3(0.0f, 0.0f, -0.5f));

        if (glIsEnabled(GL_DEPTH_TEST)) {
            glDisable(GL_DEPTH_TEST);
        }
    };

	void Renderer::setup3D() {
        _shader = new Shader("../resources/shaders/default3D_vert.glsl", "../resources/shaders/default3D_frag.glsl");
        _camera = new Camera3D(_window->getWidth(), _window->getHeight());
        _camera->setPos(glm::vec3(0.0f, 0.0f, 5.0f));

        if (!glIsEnabled(GL_DEPTH_TEST)) {
            glEnable(GL_DEPTH_TEST);
        }
    };

    void Renderer::addMesh(MeshBase* mesh)
    {
        _renderQueue.push_back(mesh);
    };

    void Renderer::removeMesh(MeshBase* mesh)
    {
        if (_renderQueue.empty()) {
            std::cerr << "No meshes to remove." << std::endl;
            return;
        }
        auto it = std::remove(_renderQueue.begin(), _renderQueue.end(), mesh);
        if (it != _renderQueue.end()) {
            _renderQueue.erase(it);
        } else {
            std::cerr << "Mesh not found in the list." << std::endl;
        }
    };

    void Renderer::clearBuffer(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    };

    void Renderer::swapBuffer()
    {
        glfwSwapBuffers(_window->getGLFWwindow());
    };

    void Renderer::render()
    {
        _shader->activate();
        _camera->update(90.0f, 0.1f, 100.0f, _shader->id);

        for (MeshBase* mesh : _renderQueue)
        {
            mesh->draw();
        }
    };

    void Renderer::reset()
    {
        if (_shader) {
            _shader->terminate();
            delete _shader;
        }
        if (_renderQueue.size() > 0) {
            for (auto* mesh : _renderQueue) {
                delete mesh;
            }
            _renderQueue.clear();
        }
        if (_camera) {
            delete _camera;
            _camera = nullptr; 
        }
    };

    GLuint Renderer::getShaderID() const
    {
        return _shader ? _shader->id : 0;
    };

    void Renderer::setShader(Shader* shader)
    {
        if (_shader) {
            _shader->terminate();
            delete _shader;
        }
        _shader = shader;
    };

    void Renderer::setCamera(Camera* cam)
    {
        if (_camera) {
            delete _camera;
        }
        _camera = cam;
    };

    Camera* Renderer::getCamera() const 
    { 
        return _camera; 
    };
};