#pragma once

#include <GL/glew.h>

#include <iostream>

/* Window stuff */
extern int width;
extern int height;

/* OpenGL Error Handling */
// ASSERT Macro
#define ASSERT(x) if (!(x)) __debugbreak();

// GLCall
// GLClearError() and GLLogCall() are defined in main.cpp
void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))