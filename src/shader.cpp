#include "shader.h"

unsigned int ID;

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
	std::string vertexCode;
	std::string fragCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	//Copy/pasted this from learnopengl
    //First, get the shader source code into string :D
    try
    {
        // open files
        vShaderFile.open(vertexShaderPath);
        fShaderFile.open(fragmentShaderPath);
        if (!vShaderFile || !fShaderFile) {
            std::cerr << "Shader file(s) not found: "
                << vertexShaderPath << " or " << fragmentShaderPath << '\n';
            return;
        }
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragCode.c_str();

    //Then, compile the shader!
    unsigned int vertexShader, fragmentShader;
    int success;
    char infoLog[512];
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);

    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    //TODO error handling


    //Create shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    //Error handling here too,
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    //Clean up!
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
void Shader::use() {
	glUseProgram(ID);
}


