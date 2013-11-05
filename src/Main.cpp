#include <stdio.h>
#include "Render.h"
#include "Scene.h"

void mainloop();
void idlefunc();
Scene* initScene();
Render* initRender();
void initGLUT(char**, int);
Scene* s;
Render* r;


int main(int argc, char *argv[])
{
    printf("Starting Simulator!\n");
    s = initScene();
    r = initRender();


    initGLUT(argv, argc);

    delete s;
    delete r;
    return 0;
}


Scene* initScene(){
    return NULL;
}

Render* initRender(){
    return NULL;
}

void initGLUT(char *argv[], int argc){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(400, 300);
    glutCreateWindow("CS194 Physics");
    glutDisplayFunc(&mainloop);
    glutIdleFunc(&idlefunc);
}

void mainloop(){
    //Render Scene
    //Render.draw(Scene)
    
    //Physics Update
    //Physics.update(Scene)

    //User Input
    //blah
}

void idlefunc(){
    
}
