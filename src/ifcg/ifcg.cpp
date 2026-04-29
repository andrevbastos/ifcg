#include "ifcg/ifcg.hpp"

namespace ifcg
{
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    std::unique_ptr<IFCG> IFCG::_instance = nullptr;
    double IFCG::_frameTimeTarget = 0.0;

    std::unique_ptr<Context> IFCG::_context = nullptr;
    std::unique_ptr<Window> IFCG::_window = nullptr;
    std::unique_ptr<Renderer> IFCG::_renderer = nullptr;
    std::unique_ptr<Keys> IFCG::_keys = nullptr;

    IFCG::IFCG(unsigned int w, unsigned int h, const char* title)
    {
        _context = std::make_unique<Context>();   
        _window = std::make_unique<Window>(w, h, title);
        _renderer = std::make_unique<Renderer>(*_window);
        _keys = std::make_unique<Keys>(*_window);

        _keys->addKeyCallback(GLFW_KEY_ESCAPE, []() {
            if (_keys->isKeyReleased(GLFW_KEY_ESCAPE))
                glfwSetWindowShouldClose(_window->getGLFWwindow(), true);
        });
    };

    IFCG::~IFCG()
    {
        _keys.reset();
        _renderer.reset();
        _window.reset();
        _context->terminate();
        _context.reset();
    };

    void IFCG::init(unsigned int w, unsigned int h, const char* title)
    {
        if (_instance == nullptr)
        {
            _instance = std::unique_ptr<IFCG>(new IFCG(w, h, title));
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

    Keys& IFCG::getInputHandler()
    {
        return *_keys;
    };

    Renderer& IFCG::getRenderer() 
    { 
        return *_renderer; 
    };

    bool IFCG::isRunning() {
        return !_window->shouldClose();
    }

    void IFCG::pollEvents() {
        _context->pollEvents();
    }

    void IFCG::releaseContext() {
        glfwMakeContextCurrent(nullptr);
    }

    void IFCG::setFramesPerSecond(int fps) {
        if (fps > 0) {
            _frameTimeTarget = 1.0 / static_cast<double>(fps);
        } else {
            _frameTimeTarget = 0.0;
        }
    }

    void IFCG::loop(LoopConfig config)
    {
        while (!_window->shouldClose())
        {
            config.beforeInputs();

            _context->pollEvents();
            _keys->update();
            _keys->processInput();
            
            config.afterInputs();
            
            _renderer->clearBuffer(1.0f, 1.0f, 1.0f, 1.0f);
            
            config.loopBody();

            _renderer->getCamera().inputs(_window->getGLFWwindow());
            _renderer->render();
            _renderer->swapBuffer();
            
            config.afterRender();

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
        config.onExit();
    }

    void IFCG::loopP(std::stop_token st, LoopConfig config)
    {
        glfwMakeContextCurrent(_window->getGLFWwindow());

        while (!_window->shouldClose() && !st.stop_requested())
        {
            config.beforeInputs();

            _keys->update();
            _keys->processInput();
            
            config.afterInputs();
            _renderer->clearBuffer(1.0f, 1.0f, 1.0f, 1.0f);
            config.loopBody();
            _renderer->getCamera().inputs(_window->getGLFWwindow());
            _renderer->render();
            _renderer->swapBuffer();
            config.afterRender();

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
        config.onExit();
    }

    void IFCG::terminate() {
        _keys.reset();
        _renderer.reset();
        _window.reset();
        if (_context) {
            _context->terminate();
            _context.reset();
        }
        _instance.reset();
    }
}