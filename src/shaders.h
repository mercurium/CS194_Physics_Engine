#pragma once
#include <iostream>
#include <string>
#define EXTERNO 

class Shader{

    public:
        Shader();
        virtual ~Shader();
        EXTERNO GLuint vertexshader;
        EXTERNO GLuint fragmentshader;
        EXTERNO GLuint shaderprogram;
        EXTERNO GLuint enablelighting;
        EXTERNO GLuint lightpos;
        EXTERNO GLuint lightcol;
        EXTERNO GLuint numused;
        EXTERNO GLuint ambientcol;
        EXTERNO GLuint diffusecol;
        EXTERNO GLuint specularcol;
        EXTERNO GLuint emissioncol;
        EXTERNO GLuint shininesscol;
};

std::string textFileRead (const char * filename) ;
void programerrors (const GLint program) ;
void shadererrors (const GLint shader) ;
GLuint initshaders (GLenum type, const char * filename) ;
GLuint initprogram (GLuint vertexshader, GLuint fragmentshader);

