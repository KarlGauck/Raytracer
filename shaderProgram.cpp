#include "shaderProgram.hpp"

#include <stdio.h>

ShaderProgram::ShaderProgram() {
    this->id = glCreateProgram();
}

void ShaderProgram::attachShader(GLuint shaderId) {
    glAttachShader(this->id, shaderId);
}

void ShaderProgram::link() {
    glLinkProgram(this->id);

    GLint programSuccess = GL_TRUE;
    glGetProgramiv(this->id, GL_LINK_STATUS, &programSuccess);
    if (programSuccess != GL_TRUE) {
        printf("Error linking program %d!\n", this->id);
        return;
    }
}