#include "shader.hpp"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>

#include "shaderProgram.hpp"

Shader::Shader(GLenum type, ShaderProgram* program, std::string sourcePath) {
    this->id = glCreateShader(type);

    std::ifstream file(sourcePath);
    if (!file.is_open()) {
        printf("Error loading shader: Source Path doesn't exist: \n");
        std::cout << sourcePath << std::endl;
        return;
    }

    std::string rawShaderSource = "";
    std::string line;
    int lineCount = 0;
    while (getline(file, line)) {
        if (lineCount > 0)
            rawShaderSource += "\n";
        lineCount ++;
        rawShaderSource += line; 
    }
    const char* shaderSource = rawShaderSource.c_str();

    std::cout << rawShaderSource;

    glShaderSource(this->id, 1, &shaderSource, NULL);
    glCompileShader(this->id);

    GLint shaderCompiled = GL_FALSE;
    glGetShaderiv(this->id, GL_COMPILE_STATUS, &shaderCompiled);
    if (shaderCompiled != GL_TRUE) {
        printf("Unable to compile shader %d!\n", this->id);
        return;
    }
    
    std::cout << "works!" << std::endl;

    program->attachShader(this->id);
}