#pragma once

#include <string>

/*
	Contains all functions and stuff needed for shader usage.
	Documentation:
		- Write these 3 lines of code:
			ShaderProgramSource source = ParseShader("path/to/shader");
			unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
			glUseProgram(shader);
		- Don't forget to add this really important line of code:
			glDeleteProgram(shader)
*/

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

ShaderProgramSource ParseShader(const std::string& filePath);

unsigned int CompileShader(unsigned int type, const std::string& source);
unsigned int CreateShader(const std::string& vertShader, const std::string& fragShader);