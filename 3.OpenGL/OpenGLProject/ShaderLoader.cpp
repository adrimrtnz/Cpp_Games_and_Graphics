#include "ShaderLoader.h"

#include <iostream>
#include <fstream>
#include <vector>

/** Stores the content of the shader file in a string, and then returns that string */
std::string ShaderLoader::readShader(const char* filename) {
	std::string shaderCode;
	std::ifstream file(filename, std::ios::in);

	if (!file.good()) {
		std::cout << "Can't read file " << filename << std::endl;
		std::terminate();
	}

	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	file.seekg(0. std::ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

GLuint ShaderLoader::createShader(GLenum shaderType, std::string source, const char* shaderName) {
	int compile_result = 0;

	GLuint shader = glCreateShader(shaderType);
	const char* shader_code_ptr = source.c_str();
	const int shader_code_size = source.size();

	glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS), &compile_result);

	// Check for errors
	if (compile_result == GL_FALSE) {

		int info_log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH), &info_log_length);
		std::vector<char> shader_log(info_log_length);
		glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
		std::cout << "ERROR compiling shader: " << shaderName << std::endl << &shader_log[0] << std::endl;
		
		return 0;
	}

	return shader;
}