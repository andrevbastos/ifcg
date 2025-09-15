/**
 * @file shader.hpp
 * @author andrevbastos (andrev.bastos28@gmail.com)
 * @brief Header file for the Shader class.
 * @details This file defines the Shader class, which encapsulates the functionality
 *          for loading, compiling, and using vertex and fragment shaders in OpenGL.
 * @copyright Copyright (c) 2025
 */
#pragma once

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

namespace shader
{
	/**
	 * @class Shader
	 * @brief Class for managing OpenGL shaders.
	 * @details This class provides methods to load, compile, and use vertex and fragment shaders.
	 */
	class Shader
	{
	public:
		// OpenGL ID for the shader program
		GLuint id;

		/** 
		 * @brief Construct a new Shader object.
		 * @param vertexFile Path to the vertex shader source file.
		 * @param fragmentFile Path to the fragment shader source file.
		 */
		Shader(const char* vertexFile, const char* fragmentFile);
		
		/** 
		 * @brief Activate the shader program.
		 */
		void activate();
		/**
		 * @brief Terminate the shader program.
		 */
		void terminate();
	private:
		/**
		 * @brief Check and print compile/link errors for shaders.
		 * @param shader The shader or program ID.
		 * @param type The type of shader ("VERTEX", "FRAGMENT", "PROGRAM").
		 */
		void compileErrors(unsigned int shader, const char* type);
	};
}

using namespace shader;