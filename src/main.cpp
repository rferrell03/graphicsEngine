#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

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
	GLFWwindow* window = glfwCreateWindow(1200, 600, "probably an epic graphical render", NULL, NULL);
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
	glViewport(0, 0, 1200, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	/////////////////--- END WINDOW SETUP ---////////////////////////

	/////////////////
	// PIPELINE ?? //
	/////////////////

	//Vertex input
	float vertices[] = {
		// Format: x, y, z, r, g, b, u, v
		-0.8f, -0.8f, 0.0f, 1, 0, 0, 0.0f, 0.0f,
		 0.8f, -0.8f, 0.0f, 0, 1, 0, 1.0f, 0.0f,

		-0.8f, -0.64f, 0.0f, 1, 0, 0, 0.0f, 0.1f,
		 0.8f, -0.64f, 0.0f, 0, 1, 0, 1.0f, 0.1f,

		-0.8f, -0.48f, 0.0f, 1, 0, 0, 0.0f, 0.2f,
		 0.8f, -0.48f, 0.0f, 0, 1, 0, 1.0f, 0.2f,

		-0.8f, -0.32f, 0.0f, 1, 0, 0, 0.0f, 0.3f,
		 0.8f, -0.32f, 0.0f, 0, 1, 0, 1.0f, 0.3f,

		-0.8f, -0.16f, 0.0f, 1, 0, 0, 0.0f, 0.4f,
		 0.8f, -0.16f, 0.0f, 0, 1, 0, 1.0f, 0.4f,

		-0.8f,  0.0f,  0.0f, 1, 0, 0, 0.0f, 0.5f,
		 0.8f,  0.0f,  0.0f, 0, 1, 0, 1.0f, 0.5f,

		-0.8f,  0.16f, 0.0f, 1, 0, 0, 0.0f, 0.6f,
		 0.8f,  0.16f, 0.0f, 0, 1, 0, 1.0f, 0.6f,

		-0.8f,  0.32f, 0.0f, 1, 0, 0, 0.0f, 0.7f,
		 0.8f,  0.32f, 0.0f, 0, 1, 0, 1.0f, 0.7f,

		-0.8f,  0.48f, 0.0f, 1, 0, 0, 0.0f, 0.8f,
		 0.8f,  0.48f, 0.0f, 0, 1, 0, 1.0f, 0.8f,

		-0.8f,  0.64f, 0.0f, 1, 0, 0, 0.0f, 0.9f,
		 0.8f,  0.64f, 0.0f, 0, 1, 0, 1.0f, 0.9f,

		-0.8f,  0.8f,  0.0f, 1, 0, 0, 0.0f, 1.0f,
		 0.8f,  0.8f,  0.0f, 0, 1, 0, 1.0f, 1.0f
	};

	/*unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};*/
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Set up shader

	Shader myShader(vertexShaderSource, fragShaderSource);
	GLint timeLoc = glGetUniformLocation(myShader.ID, "time");
	//Transform stuff

	//set up texture
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char* data = stbi_load("textures/aaa.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	//wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	int count = 0;
	//render loop!
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		glClearColor(0.3, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		float currentTime = (float)glfwGetTime();
		myShader.use();
		glUniform1f(timeLoc, currentTime);


		//Transformation calculation
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::rotate(trans, currentTime, glm::vec3(0.0, 0.0, 5.0));
		trans = glm::scale(trans, glm::vec3(0.5, (sin(currentTime)+1)/2, 0.5));
		myShader.setMat4("transform", trans);



		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
		for (int i = 0; i < 10; ++i) {
			glUniform1f(timeLoc, currentTime - i * 0.1f);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 22);
		}

		

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
