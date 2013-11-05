#include <stdio.h>
#include <glm/glm.hpp>
#include "Render.h"
#include "Scene.h"

void mainloop();
void idlefunc();
void reshape(int w, int h);
Scene* initScene();
Render initRender();
void initGLUT(char**, int);
Scene* s;
Render r;


int main(int argc, char *argv[])
{
    printf("Starting Simulator!\n");
    s = initScene();
    r = initRender();


    initGLUT(argv, argc);
    glutMainLoop();



    delete s;
    return 0;
}


Scene* initScene(){
    return NULL;
}

Render initRender(){
    return Render();
}

void initGLUT(char *argv[], int argc){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(400, 300);
    glutCreateWindow("CS194 Physics");
    glutDisplayFunc(&mainloop);
    glutReshapeFunc(&reshape);

    //glutIdleFunc(&idlefunc);
}

void mainloop(){
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Render Scene
    //Render.draw(Scene)
    r.drawtest();
    
    //Physics Update
    //Physics.update(Scene)

    //User Input
    //blah
    glutSwapBuffers();
}

void idlefunc(){
    
}

void reshape(int w, int h){
    //printf("Reshape: w:%d, h:%d\n",w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glm::mat4 p = r.getPerspective( ((float)w)/((float)h));    
    glLoadMatrixf(&p[0][0]);
    glViewport(0,0,w,h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
