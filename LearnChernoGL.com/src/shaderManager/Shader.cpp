#include "Shader.h"
#include <fstream>
#include <sstream>

// NEW: Function to parse from two separate files
ShaderProgramSource ParseShaderFromFiles(const std::string& vertexPath, const std::string& fragmentPath)
{
	auto parse = [](const std::string& path) {
		std::ifstream stream(path);
		std::stringstream ss;
		std::string line;

		if (!stream.is_open()) {
			std::cout << "Warning: Could not open shader file at: " << path << std::endl;
		}

		while (getline(stream, line)) {
			ss << line << '\n';
		}
		return ss.str();
	};

	return { parse(vertexPath), parse(fragmentPath) };
}

// Keep your original for backward compatibility or remove if not needed
ShaderProgramSource ParseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);
	std::string line;
	std::stringstream ss[2];
	enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos) type = ShaderType::FRAGMENT;
		}
		else if (type != ShaderType::NONE) {
			ss[(int)type] << line << '\n';
		}
	}
	return { ss[0].str(), ss[1].str() };
}

unsigned int CompileShader(unsigned int type, const std::string& source)
{
	GLCall(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE) {
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;
		GLCall(glDeleteShader(id));
		return 0;
	}
	return id;
}

unsigned int CreateShader(const std::string& vertShader, const std::string& fragShader)
{
	GLCall(unsigned int program = glCreateProgram());
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}