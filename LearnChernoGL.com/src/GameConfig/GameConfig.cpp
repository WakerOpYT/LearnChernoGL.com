#include "GameConfig.h"

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum err = glGetError())
	{
		std::cout << "[OpenGL Error] (" << err << "): " << function << " " << file << ": " << line << std::endl;
		return false;
	}
	return true;
}