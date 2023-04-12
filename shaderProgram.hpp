#pragma once

#include <GL/glew.h>
#include <GL/glu.h>

class ShaderProgram {
    public:
        GLuint id;
        ShaderProgram();
        void attachShader(GLuint shaderId);
        void link();
};