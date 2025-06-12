#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void compileShader(int shader, const char* shaderSource); 

const char* vertexShaderSource = "shaders/first.vs";

const char* fragShaderSource = "shaders/first.fs";


int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	////////////////////
	////WINDOW SETUP////
	////////////////////

	//Creates window
	GLFWwindow* window = glfwCreateWindow(800, 600, "triangle window", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	//Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	/////////////////--- END WINDOW SETUP ---////////////////////////

	/////////////////
	// PIPELINE ?? //
	/////////////////

	//Vertex input
	float vertices[] = {//(pos)(color)
	-1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	 1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	-1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Set up shader

	Shader myShader(vertexShaderSource, fragShaderSource);

	//wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	int count = 0;
	//render loop!
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		

		myShader.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		

		// check and call events and swap the buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return 0;
}



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
