//
// Created by Igor Alentev on 03.01.2023.
//

#ifndef PASCALWINGS_SHADERPROGRAM_H
#define PASCALWINGS_SHADERPROGRAM_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ShaderProgram {
    unsigned int ID;
    unsigned int vertexShader;
    unsigned int fragmentShader;

    std::string readShaderFile(const char *shaderPath);

public:
    ShaderProgram();
    void setShader(const char *shaderPath, GLenum shaderType);
    void linkShaders();
    void use();
    unsigned int getID();
};


#endif //PASCALWINGS_SHADERPROGRAM_H
