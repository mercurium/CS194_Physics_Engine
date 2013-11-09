#include <stdio.h>
#include <glm/glm.hpp>
#include "Render.h"

void mainloop();
void idlefunc();
void reshape(int w, int h);
void key(unsigned char c, int x, int y);
void mouse( int button, int state, int x, int y);
Render initRender();
void initGLUT(char**, int);
Render r;
int mouse_left_down_x;
int mouse_left_down_y;
int mouse_right_down_x;
int mouse_right_down_y;
std::vector<Sphere *> balls;

int main(int argc, char *argv[])
{
    printf("Starting Simulator!\n");

    mouse_left_down_x=0;
    mouse_left_down_y=0;
    mouse_right_down_x=0;
    mouse_right_down_y=0;
    r = initRender();

    initGLUT(argv, argc);
	balls = Scene::makeTestScene();
    glutMainLoop();



    return 0;
}

Render initRender(){
    return Render();
}

void initGLUT(char *argv[], int argc){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("CS194 Physics");
    glutDisplayFunc(&mainloop);
    glutReshapeFunc(&reshape);
    glutKeyboardFunc(&key);
    glutMouseFunc(&mouse);

    //glutIdleFunc(&idlefunc);
}

void mainloop(){
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Render Scene
	Scene::UpdateScene(*(&balls));
    r.draw(balls);
    //r.drawtest();
    
    //Physics Update
    //Physics.update(Scene)

    //User Input
    //blah
    glutSwapBuffers();
}

void key(unsigned char c, int x, int y){
    const double SNSTVTY = 0.5;
    switch(c){
        case 'w':
            r.translCamFB(SNSTVTY);
            break;
        case 's':
            r.translCamFB(-SNSTVTY);
            break;
        case 'a':
            r.translCamLR(SNSTVTY);
            break;
        case 'd':
            r.translCamLR(-SNSTVTY);
            break;

        case 'i':
            r.rotateCamUD(10*SNSTVTY);
            break;
        case 'k':
            r.rotateCamUD(-10*SNSTVTY);
            break;
        case 'j':
            r.rotateCamLR(10*SNSTVTY);
            break;
        case 'l':
            r.rotateCamLR(-10*SNSTVTY);
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
