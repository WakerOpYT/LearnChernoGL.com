#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "GameConfig/GameConfig.h"
#include "shaderManager/Shader.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Renderer.h"


void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
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

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

    {
    float vertices[] = {
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
    // VBO & VAO
    VertexBuffer vbo(vertices, 4 * 2 * sizeof(float));
    VertexArray vao;
    VertexBufferLayout layout;
    layout.Push<float>(2);
    vao.AddBuffer(vbo, layout);

    // IBO
    IndexBuffer ibo(indices, 6);
    

    /* Shaders */
    ShaderProgramSource source = ParseShaderFromFiles("res/shaders/vert-basic.shader", "res/shaders/frag-basic.shader");
    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    GLCall(glUseProgram(shader));


    /* Game Loop (Preparation) */
    GLCall(glBindVertexArray(0));
    GLCall(glUseProgram(0));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

    /* Game Loop */
    while (!glfwWindowShouldClose(window))
    {
        GLCall(glUseProgram(shader));
        vao.Bind();
        ibo.Bind();

        processInput(window);

        GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
        GLCall(glfwSwapBuffers(window));
        GLCall(glfwPollEvents());
    }

    /* Termination */
    GLCall(glDeleteProgram(shader));
    }
    glfwTerminate();
    return 0;
}