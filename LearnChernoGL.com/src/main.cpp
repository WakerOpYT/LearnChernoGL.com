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
		window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);

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
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);

	// IBO
	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	
	/* Shaders */
	ShaderProgramSource source = ParseShader("res/shaders/basic.shader");
	unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
	glUseProgram(shader);

	/* Game Loop */
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	/* Termination */
	glDeleteProgram(shader);
	glfwTerminate();
	return 0;
}