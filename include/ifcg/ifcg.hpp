#pragma once

/**
* \author André B.
* \date March 20, 2025
* \version March 20, 2025
* \brief Constructor for IFCG class using Singleton pattern
**/

#ifndef IFCG_API
    #ifdef _WIN32
        #ifdef IFCG_EXPORTS
            #define IFCG_API __declspec(dllexport)
        #else
            #define IFCG_API __declspec(dllimport)
        #endif
    #else
        #define IFCG_API
    #endif
#endif

#include <iostream>
#include <algorithm>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <functional>
#include <thread>
#include <chrono>

#include "ifcg/shader/shader.hpp"
#include "ifcg/common/mesh.hpp"
#include "ifcg/common/camera.hpp"

#include "ifcg/graphics2D/scene/camera.hpp"
#include "ifcg/graphics3D/scene/camera.hpp"
#include "ifcg/graphics2D/geometry/mesh.hpp"
#include "ifcg/graphics3D/geometry/mesh.hpp"

namespace ifcg
{
    class IFCG
	{
	public:
		static void init();

		static void setFramesPerSecond(int fps);
        static void loop(const std::function<void()>& gameLoopBody);
		static void createWindow(GLuint w, GLuint h);
		static void destroyWindow();
		static bool shouldClose();
    	static void clearBuffer(float r, float g, float b, float a = 1.0f);
		static void readInputs();
		static void processInput();
		static void swapBuffer();
		
		static void setup2D();
		static void setup3D();

		static void addMesh(Mesh* mesh);
		static void removeMesh(Mesh* mesh);
		static void render();
		
		static void terminate();
		
		IFCG_API static GLFWwindow* window;
		IFCG_API static Camera* camera;
		IFCG_API static Shader shader;
		
		IFCG_API static std::vector<Mesh*> renderQueue;
		IFCG_API static GLuint width;
		IFCG_API static GLuint height;
		
	private:
		IFCG();
		static void terminate_();
		
		IFCG_API static IFCG* instance;
		IFCG_API static double frameTimeTarget; 
	};
};

using namespace ifcg;