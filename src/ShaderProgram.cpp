//
// Created by Igor Alentev on 03.01.2023.
//

#include "ShaderProgram.h"

void ShaderProgram::use() {
    glUseProgram(this->ID);
}

ShaderProgram::ShaderProgram() {
    this->ID = 0;
    this->vertexShader = 0;
    this->fragmentShader = 0;
}

void ShaderProgram::setShader(const char *shaderPath, GLenum shaderType) {
    std::string shaderCode = this->readShaderFile(shaderPath);
    const char *shaderCodeC = shaderCode.c_str();

    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCodeC, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    } else {
        if (shaderType == GL_VERTEX_SHADER) {
            this->vertexShader = shader;
#ifdef VERBOSE
            std::cout << "Vertex shader compiled successfully" << std::endl;
#endif
        } else if (shaderType == GL_FRAGMENT_SHADER) {
            this->fragmentShader = shader;
#ifdef VERBOSE
            std::cout << "Fragment shader compiled successfully" << std::endl;
#endif
        }
    };
}

std::string ShaderProgram::readShaderFile(const char *shaderPath) {
    std::string shaderCode;
    std::ifstream shaderFile;
    shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        shaderFile.open(shaderPath);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        shaderCode   = shaderStream.str();
    }
    catch(std::ifstream::failure &e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
        return {};
    }

#ifdef VERBOSE
    std::cout << "Shader file read successfully" << std::endl;
#endif

    return shaderCode;
}

void ShaderProgram::linkShaders() {
    this->ID = glCreateProgram();
    glAttachShader(this->ID, this->vertexShader);
    glAttachShader(this->ID, this->fragmentShader);
    glLinkProgram(this->ID);

    int success;
    char infoLog[512];
    glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(this->vertexShader);
    glDeleteShader(this->fragmentShader);
}

unsigned int ShaderProgram::getID() {
    return this->ID;
}
