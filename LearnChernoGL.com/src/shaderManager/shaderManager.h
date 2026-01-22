#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include "../GameConfig/GameConfig.h"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

ShaderProgramSource ParseShader(const std::string& filePath);

unsigned int CompileShader(unsigned int type, const std::string& source);

unsigned int CreateShader(const std::string& vertShader, const std::string& fragShader);