#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <string>

#include "shaderProgram.hpp"
#include "shader.hpp"

bool init();

bool initGL();

void handleKeys( unsigned char key, int x, int y );

void update();

void render();

void close();

void printProgramLog(GLuint program);

void printShaderLog(GLuint shader);

SDL_Window* gWindow = NULL;
SDL_GLContext gContext;
bool gRenderQuad = true;
int SCREEN_WIDTH = 1600;
int SCREEN_HEIGHT = 900;

ShaderProgram* program;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not be initialiized! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    gWindow = SDL_CreateWindow("Raytracer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    
    if (gWindow == NULL) {
        printf("Window could net be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    gContext = SDL_GL_CreateContext(gWindow);

    if (gContext == NULL) {
        printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();

    if (glewError != GLEW_OK) {
        printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
    }


    if (SDL_GL_SetSwapInterval(1) < 0)
        printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());

    if (!initGL()) {
        printf("Unable to initialize OpenGL!\n");
        return false;
    }

    return true;
}


bool initGL() {
    /*
    program = new ShaderProgram();
    Shader* vertexShader = new Shader(GL_VERTEX_SHADER, program, "/home/karlg/dev/raytracer/vertexShader.glsl");
    Shader* fragmentShader = new Shader(GL_FRAGMENT_SHADER, program, "/home/karlg/dev/raytracer/fragmentShader.glsl");

    program->link();
    */

    float positions[6] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);    
    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), &positions, GL_STATIC_DRAW);

    return true;
}

void handleKeys(unsigned char key, int x, int y) {
    if (key == 'q')
        gRenderQuad = !gRenderQuad;
}

void update() {

}

void render() {
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main( int argc, char* args[] ) {
    init();

    SDL_StartTextInput();
    SDL_Event e;

    bool quit = false;
    while(!quit) {

        while(SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                quit = true;

            else if (e.type == SDL_TEXTINPUT) {
                int x = 0, y = 0;
                SDL_GetMouseState(&x, &y);
                handleKeys(e.text.text[0], x, y);
            }
        }

        render();

        SDL_GL_SwapWindow(gWindow);
    }

    SDL_StopTextInput();
    close();
}


void close() {
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}