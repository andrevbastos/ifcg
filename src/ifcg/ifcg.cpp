#include "ifcg/ifcg.hpp"

namespace ifcg
{
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	IFCG* IFCG::_instance = nullptr;
    double IFCG::_frameTimeTarget = 0.0;

    Context* IFCG::_context = nullptr;
    Window* IFCG::_window = nullptr;
    Renderer* IFCG::_renderer = nullptr;
    Keys* IFCG::_keys = nullptr;

    IFCG::IFCG(unsigned int w, unsigned int h, const char* title)
    {
        _context = new Context();   
        _window = new Window(w, h, title);
        _renderer = new Renderer(_window);
        _keys = new Keys(_window);

        _keys->addKeyCallback(GLFW_KEY_ESCAPE, []() {
            if (_keys->isKeyReleased(GLFW_KEY_ESCAPE))
                glfwSetWindowShouldClose(_window->getGLFWwindow(), true);
        });
    };

    IFCG::~IFCG()
    {
        delete _keys;
        delete _renderer;
        delete _window;
        _context->terminate();
        delete _context;
    };

    void IFCG::init(unsigned int w, unsigned int h, const char* title)
    {
        if (_instance == nullptr)
        {
            _instance = new IFCG(w, h, title);
        }
    };

    void IFCG::setup2D() 
    {
        _renderer->reset();
        _renderer->setup2D();
    };
		
    void IFCG::setup3D() 
    {
        _renderer->reset();
        _renderer->setup3D();
    };

    Keys* IFCG::getInputHandler()
    {
        return _keys;
    };

    Renderer* IFCG::getRenderer() 
    { 
        return _renderer; 
    };

    void IFCG::setFramesPerSecond(int fps) {
        if (fps > 0) {
            _frameTimeTarget = 1.0 / static_cast<double>(fps);
        } else {
            _frameTimeTarget = 0.0;
        }
    }

    void IFCG::loop(const std::function<void()>& loopBody)
    {
        while (!_window->shouldClose())
        {
            _context->pollEvents();
            _keys->update();
            _keys->processInput();
            _renderer->clearBuffer(1.0f, 1.0f, 1.0f, 1.0f);
            
            loopBody();
            
            _renderer->getCamera()->inputs(_window->getGLFWwindow());
            _renderer->render();
            _renderer->swapBuffer();
            
            double startTime = glfwGetTime();
            if (_frameTimeTarget > 0.0)
            {
                double endTime = glfwGetTime();
                double frameDuration = endTime - startTime;
                if (frameDuration < _frameTimeTarget)
                {
                    int sleepTimeMs = static_cast<int>((_frameTimeTarget - frameDuration) * 1000.0);
                    if (sleepTimeMs > 0)
                    {
                        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTimeMs));
                    }
                }
            }
        }
    }

    void IFCG::terminate()
    {
        delete _instance;
        _instance = nullptr;
    };
}