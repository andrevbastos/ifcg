#include "ifcg/components/renderer.hpp"

namespace ifcg
{
    Renderer::Renderer(Window& win)
        : _renderQueue({}), _window(win) {}

    void Renderer::setup2D() {
        _shader = std::make_shared<Shader>("../resources/shaders/default2D_vert.glsl", "../resources/shaders/default2D_frag.glsl");
        _camera = std::make_shared<Camera>(_window.getWidth(), _window.getHeight());
        _camera->setPos(glm::vec3(0.0f, 0.0f, -0.5f));

        if (glIsEnabled(GL_DEPTH_TEST)) {
            glDisable(GL_DEPTH_TEST);
        }
    }

    void Renderer::setup3D() {
        _shader = std::make_shared<Shader>("../resources/shaders/default3D_vert.glsl", "../resources/shaders/default3D_frag.glsl");
        _camera = std::make_shared<Camera>(_window.getWidth(), _window.getHeight());
        _camera->setPos(glm::vec3(0.0f, 0.0f, 5.0f));

        if (!glIsEnabled(GL_DEPTH_TEST)) {
            glEnable(GL_DEPTH_TEST);
        }
    }

    void Renderer::addMesh(std::shared_ptr<MeshBase> mesh)
    {
        if (mesh) {
            _renderQueue.push_back(mesh);
        }
    }

    void Renderer::removeMesh(std::shared_ptr<MeshBase> mesh)
    {
        auto it = std::find(_renderQueue.begin(), _renderQueue.end(), mesh);
        if (it != _renderQueue.end()) {
            _renderQueue.erase(it);
        } else {
            std::cerr << "Mesh not found in the list." << std::endl;
        }
    }

    void Renderer::clearBuffer(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::swapBuffer()
    {
        glfwSwapBuffers(_window.getGLFWwindow());
    }

    void Renderer::render()
    {
        if (!_shader || !_camera) return;

        _shader->activate();
        _camera->update(_fov, _nearPlane, _farPlane, _shader->id);

        for (const auto& mesh : _renderQueue)
        {
            if (mesh) {
                mesh->draw();
            }
        }
    }

    void Renderer::reset()
    {
        if (_shader) {
            _shader->terminate();
        }
        
        _shader.reset();
        _camera.reset();
        _renderQueue.clear(); 
    }

    GLuint Renderer::getShaderID() const
    {
        return _shader ? _shader->id : 0;
    }

    Camera& Renderer::getCamera() const
    {
        return *_camera;
    }

    void Renderer::setShader(std::shared_ptr<Shader> shader)
    {
        if (_shader) {
            _shader->terminate();
        }
        _shader = shader; 
    }

    void Renderer::setCamera(std::shared_ptr<Camera> cam)
    {
        _camera = cam;
    }
}