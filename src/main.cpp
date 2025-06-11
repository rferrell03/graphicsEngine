#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void compileShader(int shader, const char* shaderSource); 

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(0.5f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

const char* yellowFragShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1f, 1f, 0.0f, 1.0f);\n"
"}\0";

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
	float vertices[] = {
	 0.0f,  0.0f, 0.0f,  
	 0.5f,  0.5f, 0.0f, 
	 0.5f,  0.0f, 0.0f,  
	 0.25f, 0.5f, 0.0f,
	 0.75f, 0.5f, 0.0f,
	 0.5f,  1.0f,  0.0f,
	};

	unsigned int indices[] = {
		0,1,2, //first triangle
		3,4,5 //second triangle
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Compile vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	compileShader(vertexShader, vertexShaderSource);

	//Compile frag shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	compileShader(fragmentShader, fragShaderSource);

	unsigned int yellowShader;
	yellowShader = glCreateShader(GL_FRAGMENT_SHADER);
	compileShader(yellowShader, yellowFragShaderSource);


	//Create program (holds all shaders together)
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	unsigned int yellowShaderProgram;
	yellowShaderProgram = glCreateProgram();
	glAttachShader(yellowShaderProgram, vertexShader);
	glAttachShader(yellowShaderProgram, yellowShader);
	glLinkProgram(yellowShaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//this seems like an awful lot of boilerplate

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

		glUseProgram(count++ >= 1000 ? shaderProgram : yellowShaderProgram);
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


//Compiles the shader
void compileShader(int shader, const char* shaderSource) {
	glShaderSource(shader, 1, &shaderSource, 0);
	glCompileShader(shader);
}