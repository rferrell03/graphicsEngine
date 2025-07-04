
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <random>
#include <iostream>
#include "shader.h"
#include "texture.h"
#include "mesh.h"
#include "VertexLayout.h"
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

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, 1200, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	/////////////////--- END WINDOW SETUP ---////////////////////////

	/////////////////
	// PIPELINE ?? //
	/////////////////

	//Vertex input
	float vertices[] = {
		// Back face
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		// Front face
		-0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 0.0f,

		// Left face
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		// Right face (FIXED)
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		 // Bottom face
		 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		  0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		 // Top face
		 -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	  	  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	  	 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	};

	float pyramidVertices[] = {
		// Base (two triangles)
		-0.5f, 0.0f, -0.5f,  0.0f, 0.0f, // back left
		 0.5f, 0.0f, -0.5f,  1.0f, 0.0f, // back right
		 0.5f, 0.0f,  0.5f,  1.0f, 1.0f, // front right

		-0.5f, 0.0f, -0.5f,  0.0f, 0.0f, // back left
		 0.5f, 0.0f,  0.5f,  1.0f, 1.0f, // front right
		-0.5f, 0.0f,  0.5f,  0.0f, 1.0f, // front left

		// Side 1 (back)
		-0.5f, 0.0f, -0.5f,  0.0f, 0.0f,
		 0.5f, 0.0f, -0.5f,  1.0f, 0.0f,
		 0.0f, 1.0f,  0.0f,  0.5f, 1.0f,

		 // Side 2 (right)
		  0.5f, 0.0f, -0.5f,  0.0f, 0.0f,
		  0.5f, 0.0f,  0.5f,  1.0f, 0.0f,
		  0.0f, 1.0f,  0.0f,  0.5f, 1.0f,

		  // Side 3 (front)
		   0.5f, 0.0f,  0.5f,  1.0f, 0.0f,
		  -0.5f, 0.0f,  0.5f,  0.0f, 0.0f,
		   0.0f, 1.0f,  0.0f,  0.5f, 1.0f,

		   // Side 4 (left)
		   -0.5f, 0.0f,  0.5f,  1.0f, 0.0f,
		   -0.5f, 0.0f, -0.5f,  0.0f, 0.0f,
			0.0f, 1.0f,  0.0f,  0.5f, 1.0f,
	};


	VertexLayout currLayout = {
		{
			{0, 3, 0},
			{1, 2, sizeof(float) * 3},
		},
		sizeof(float) * 5

	};


	Mesh square(vertices, sizeof(vertices), currLayout);
	Mesh pyramid(pyramidVertices, sizeof(pyramidVertices), currLayout);
	//Set up shader

	Shader myShader(vertexShaderSource, fragShaderSource);
	GLint timeLoc = glGetUniformLocation(myShader.ID, "time");
	//Transform stuff

	//set up texture
	Texture myTex("textures/aaa.jpg", true);
	Texture myTex2("textures/burger.jpg", true);



	//wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//gen cubes
	int count = 30;
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);
	std::uniform_real_distribution<float> speed(1.0f, 3.0f);
	std::uniform_real_distribution<float> speedDist(0.8f, 2.0f);
	std::uniform_real_distribution<float> distX(-3.5f, 3.5f);
	std::uniform_real_distribution<float> distY(-3.0f, 3.0f);
	std::uniform_real_distribution<float> distZ(-5.5f, -4.5f);

	std::vector<glm::vec3> cubePositions = {};
	std::vector<glm::vec3> cubeRotations;
	std::vector<float> cubeSpeeds;

	
	for (int i = 0; i < count; ++i) {
		cubeSpeeds.push_back(speedDist(gen));
		cubeRotations.emplace_back(dist(gen), dist(gen), dist(gen) );
		cubePositions.emplace_back(distX(gen), distY(gen), distZ(gen));
	}

	//render loop!
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		glClearColor(0.3, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		float currentTime = (float)glfwGetTime();
		myShader.use();
		glUniform1f(timeLoc, currentTime);

		//MVP
		glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		//model = glm::rotate(model, currentTime / 2 * glm::radians(-55.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, currentTime * glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, currentTime * glm::radians(90.0f), glm::vec3(0.0f, 0.5f, 0.0f));

		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)1200 / (float)600, 0.1f, 100.0f);

		//Transformation calculation

		myShader.setMat4("view", view);
		myShader.setMat4("projection", projection);


		myTex2.Bind();
		
		for (int i = 0; i < count; ++i) {
			glUniform1f(timeLoc, currentTime - i * 0.1f);
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::scale(model, glm::vec3(1.5));
			model = glm::rotate(model, sin(currentTime * cubeSpeeds[i]) * glm::radians(180.0f), glm::vec3(0.0,1.,0.));
			myShader.setMat4("model", model);
			if (i % 2 == 1) {
				square.draw();
			}

			else {
				
				pyramid.draw();
			}
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


