#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>

#include "GameConfig/GameConfig.h"
#include "shaderManager/shaderManager.h"

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main(void)
{
	std::cout << "Starting game..." << std::endl;
	GLFWwindow* window;

	/* Window stuff */
	{
		/* GLFW */
		if (!glfwInit())
			return -1;
		window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);

		/* GLEW */
		if (glewInit() != GLEW_OK)
			std::cout << "ERROR!" << std::endl;

		/* Other */
		std::cout << glGetString(GL_VERSION) << std::endl;
	}

	float positions[] = {
		-0.5f, -0.5f, // 0 - Bottom Left
		 0.5f, -0.5f, // 1 - Bottom Right
		 0.5f,  0.5f, // 2 - Top Right
		-0.5f,  0.5f, // 3 - Top Left
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	/* Buffers */
	// VBO
	unsigned int buffer;
	GLCall(glGenBuffers(1, &buffer));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0))

	// IBO
	unsigned int ibo;
	GLCall(glGenBuffers(1, &ibo));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW))
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));
	
	/* Shaders */
	//Shader Setup
	ShaderProgramSource source = ParseShader("res/shaders/basic.shader");
	unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
	GLCall(glUseProgram(shader));

	// Uniforms
	GLCall(int location = glGetUniformLocation(shader, "u_Color"));
	ASSERT(location != -1)
	GLCall(glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f));

	/* Game Loop */
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
		GLCall(glfwSwapBuffers(window));
		
		GLCall(glfwPollEvents());
	}

	/* Termination */
	GLCall(glDeleteProgram(shader));
	glfwTerminate();
	return 0;
}