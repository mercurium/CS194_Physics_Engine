#include <stdio.h>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Render.h"
#include "shaders.h"
#include <cstdlib>
#include <ctime>


void mainloop();
void idlefunc();
void reshape(int w, int h);
void keydown(unsigned char c, int x, int y);
void keyup(unsigned char c, int x, int y);
void mouse( int button, int state, int x, int y);
void init();
void initGLUT(char**, int);
Render* r;
int mouse_left_down_x;
int mouse_left_down_y;
int mouse_right_down_x;
int mouse_right_down_y;
char* keydict;
std::vector<Sphere *> balls;

int main(int argc, char *argv[])
{
    printf("Starting Simulator!\n");

    initGLUT(argv, argc);
    init();
	balls = Scene::makeTestScene();
    glutMainLoop();



    return 0;
}

void init(){
    mouse_left_down_x=0;
    mouse_left_down_y=0;
    mouse_right_down_x=0;
    mouse_right_down_y=0;
    std::srand(std::time(0));

    keydict = new char[256];
    for (int i=0; i<256;i++){
        keydict[i]=0;
    }


    glEnable(GL_DEPTH_TEST);
    GLenum err = glewInit();
    if( err != GLEW_OK){
        printf("Glew initialization error: %s\n", glewGetString(err));
    }

    r = new Render();

    r->shader->vertexshader = initshaders(GL_VERTEX_SHADER, "shaders/light.vert.glsl") ;
    GLuint shaderprogram;
    r->shader->fragmentshader = initshaders(GL_FRAGMENT_SHADER, "shaders/light.frag.glsl") ;
    r->shader->shaderprogram = initprogram(r->shader->vertexshader, r->shader->fragmentshader) ; 
    shaderprogram = r->shader->shaderprogram;
    r->shader->enablelighting = glGetUniformLocation(shaderprogram,"enablelighting") ;
    r->shader->lightpos = glGetUniformLocation(shaderprogram,"lightposn") ;       
    r->shader->lightcol = glGetUniformLocation(shaderprogram,"lightcolor") ;       
    r->shader->numused = glGetUniformLocation(shaderprogram,"numused") ;       
    r->shader->ambientcol = glGetUniformLocation(shaderprogram,"ambient") ;       
    r->shader->diffusecol = glGetUniformLocation(shaderprogram,"diffuse") ;       
    r->shader->specularcol = glGetUniformLocation(shaderprogram,"specular") ;       
    r->shader->emissioncol = glGetUniformLocation(shaderprogram,"emission") ;       
    r->shader->shininesscol = glGetUniformLocation(shaderprogram,"shininess") ;    

}

void initGLUT(char *argv[], int argc){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("CS194 Physics");
    glutDisplayFunc(&mainloop);
    glutReshapeFunc(&reshape);
    glutKeyboardFunc(&keydown);
    glutKeyboardUpFunc(&keyup);
    glutMouseFunc(&mouse);

    glutIdleFunc(&idlefunc);
}

void mainloop(){
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Render Scene
	Scene::UpdateScene(*(&balls));
    r->draw(balls);
    //r.drawtest();
    
    //Physics Update
    //Physics.update(Scene)

    //User Input
    //blah
    glutSwapBuffers();
}


void keyup(unsigned char c, int x, int y){
    //printf("keyup: %c\n", c);
    keydict[c]=0;
}

void keydown(unsigned char c, int x, int y){
    //printf("keydown: %c\n", c);
    keydict[c]=1;
    const double SNSTVTY = 0.5;
    switch(c){
        case 'w':
            r->translCamFB(SNSTVTY);
            break;
        case 's':
            r->translCamFB(-SNSTVTY);
            break;
        case 'a':
            r->translCamLR(SNSTVTY);
            break;
        case 'd':
            r->translCamLR(-SNSTVTY);
            break;

        case 'i':
            r->rotateCamUD(10*SNSTVTY);
            break;
        case 'k':
            r->rotateCamUD(-10*SNSTVTY);
            break;
        case 'j':
            r->rotateCamLR(10*SNSTVTY);
            break;
        case 'l':
            r->rotateCamLR(-10*SNSTVTY);
            break;

        default:
            //nothing
            break;
    }
    glutPostRedisplay();
}

void mouse( int button, int state, int x, int y){
    /*
    mouse_left_down_x=0;
    mouse_left_down_y=0;
    mouse_right_down_x=0;
    mouse_right_down_y=0;
    */
    if(button == GLUT_LEFT_BUTTON){
        if(state==GLUT_UP){
            int distx = x-mouse_left_down_x;
            int disty = y-mouse_left_down_y;
        }else if (state==GLUT_DOWN){
            mouse_left_down_x=x;
            mouse_left_down_y=y;
        }
    }else if (button ==GLUT_RIGHT_BUTTON){
        if(state==GLUT_UP){
            int distx = x-mouse_right_down_x;
            int disty = y-mouse_right_down_y;
        }else if (state==GLUT_DOWN){
            mouse_right_down_x=x;
            mouse_right_down_y=y;
        }
    }
}

void idlefunc(){
     glutPostRedisplay();   
}

void reshape(int w, int h){
    //printf("Reshape: w:%d, h:%d\n",w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glm::mat4 p = r->getPerspective( ((float)w)/((float)h));    
    glLoadMatrixf(&p[0][0]);
    glViewport(0,0,w,h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
