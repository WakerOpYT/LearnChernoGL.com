#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


/* LOG Macro */
#ifdef _DEBUG
	#define LOG(x) std::cout << x
#else
	#define LOG(x)
#endif


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};


static ShaderProgramSource ParseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);

	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		LOG("Failed to compile ");
		LOG((type == GL_VERTEX_SHADER ? "vertex shader!\n" : "fragment shader!\n"));
		LOG(message);
		LOG('\n');
		glDeleteShader(id);
		return 0;
	}

	return id;
}

static unsigned int CreateShader(const std::string& vertShader, const std::string& fragShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

int main(void)
{
	LOG("Starting game...\n");
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
			LOG("ERROR!\n");

		/* Other */
		LOG(glGetString(GL_VERSION));
		LOG('\n');
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