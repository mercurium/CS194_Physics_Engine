#include <stdio.h>
#include "Render.h"
#include "Scene.h"

void mainloop();
void idlefunc();
void initGLUT(char**, int);
Scene s;
Render r;


int main(int argc, const char *argv[])
{
    //initGLUT(argv, argc);
    printf("Hello!\n");
    return 0;
}

/*
void initGLUT(char ** argv, int argc){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(400, 300);
    glutCreateWindow("CS194 Physics");
    glutDisplayFunc(&mainloop);
    glutIdleFunc(&idlefunc);
}
*/

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
