#pragma once

#include <string>
#include <GL/glew.h>
#include "shaderProgram.hpp"

class Shader {
    private: 
        GLuint id; 
        GLenum type;
    public:
        Shader(GLenum type, ShaderProgram* program, std::string sourcePath);
};