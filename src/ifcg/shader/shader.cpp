#include "ifcg/shader/shader.hpp"

namespace shader
{

	std::string get_file_contents(const char* filename);
	std::string get_file_contents(const char* filename)
	{
		std::ifstream in(filename, std::ios::in | std::ios::binary);
		if (in)
		{
			std::ostringstream contents;
			contents << in.rdbuf();
			in.close();
			return contents.str();
		}

		std::cerr << "ERRO: Nao foi possivel abrir o arquivo do shader: " << filename << std::endl;
		return "";
	};

	Shader::Shader(const char* vertexFile, const char* fragmentFile)
	{
		std::string vertexCode = get_file_contents(vertexFile);
		std::string fragmentCode = get_file_contents(fragmentFile);

		if (vertexCode.empty() || fragmentCode.empty())
		{
            id = 0;
			std::cerr << "ERRO: Criacao do shader abortada devido a falha na leitura do arquivo." << std::endl;
			return;
		}

		const char* vertexSource = vertexCode.c_str();
		const char* fragmentSource = fragmentCode.c_str();

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		glCompileShader(vertexShader);
		compileErrors(vertexShader, "VERTEX");

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		glCompileShader(fragmentShader);
		compileErrors(fragmentShader, "FRAGMENT");

		id = glCreateProgram();
		glAttachShader(id, vertexShader);
		glAttachShader(id, fragmentShader);
		glLinkProgram(id);
		compileErrors(id, "PROGRAM");

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	};

	void Shader::activate()
	{
		glUseProgram(id);
	};

	void Shader::terminate()
	{
		glDeleteProgram(id);
	};

	void Shader::compileErrors(unsigned int shader, const char* type)
	{
		GLint hasCompiled;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
			if (hasCompiled == GL_FALSE)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
			if (hasCompiled == GL_FALSE)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
			}
		}
	};
}