#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <omp.h>

#include <glm/glm.hpp>
#include <glm/gtx/simd_vec4.hpp>
#include <GL/glew.h>

#include "Render.h"
#include "Util.h"
#include "shaders.h"

#define MAINPROGRAM
#include "Scene.h"
#include "readfile.h"

void mainloop();
void idlefunc();
void reshape(int w, int h);
void updateInputs(double elapsed);
void keydown(unsigned char c, int x, int y);
void keyup(unsigned char c, int x, int y);
void mouse( int button, int state, int x, int y);
void init();
void outputText();
void initGLUT(char**, int);

Render* r;

int mouse_left_down_x;
int mouse_left_down_y;
int mouse_right_down_x;
int mouse_right_down_y;
double prev_time;
char* keydict;
Scene scene;

int main(int argc, char *argv[])
{
    printf("Starting Simulator!\n");
    bool outputGL = false;
	Read::readfile("config.txt");
    omp_set_num_threads(8);

    if(outputGL){
        initGLUT(argv, argc);
        init();
		scene = Scene(balls, constraints, numballs, numcons);
        glutMainLoop();
    }else{
    	scene = Scene(balls, constraints, numballs, numcons);
        outputText();
    }
    return 0;
}

void init(){
    mouse_left_down_x=0;
    mouse_left_down_y=0;
    mouse_right_down_x=0;
    mouse_right_down_y=0;
    prev_time = timestamp();
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
    glutInitWindowSize(width, height);
    glutCreateWindow("CS194 Physics");
    glutDisplayFunc(&mainloop);
    glutReshapeFunc(&reshape);
    glutKeyboardFunc(&keydown);
    glutKeyboardUpFunc(&keyup);
    glutMouseFunc(&mouse);

    glutIdleFunc(&idlefunc);
}

void mainloop(){
    double current_time = timestamp();
    double elapsed = current_time-prev_time;
    prev_time = current_time;

    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Render Scene
	//Scene::UpdateScene(*(&balls), elapsed);
	scene.UpdateScene(elapsed);
    r->draw(scene.getBalls());
    //r.drawtest();
    
    //Physics Update
    //Physics.update(Scene)

    //User Input
    updateInputs(elapsed);
    //blah
    glutSwapBuffers();
}

void outputText(){
	//scene = Scene();
    double step_size = 0.1; //settings.get("stepsize")
    double total_duration = 10; //settings.get("totalsimduration")

    double current_time = timestamp();
    for(double d = 0; d<total_duration; d+= step_size){
/*		balls = scene.getBalls();
        printf("t=%.3f :", d);
        for(int i = 0; i < numballs; i++){
            Sphere s = balls[i];
            glm::vec3 pos = s.getPos();

            printf("(%.3f,%.3f,%.3f)",pos[0],pos[1],pos[2]);
        }
*/       scene.UpdateScene(step_size);        
    }
    double elapsed = timestamp() - current_time;
    balls = scene.getBalls();
    double mew = 0;
    for (int i = 0; i < numballs; i++) {
        Sphere s = balls[i];
        glm::vec3 pos = s.getPos();
        if (mew < pos[0]) mew = pos[0];
    }
    printf("largest ... x value: %.3f\n", mew);
    printf("elapsed time: %f\n", elapsed);


}

void updateInputs(double elapsed){
    const double SNSTVTY = 10*elapsed;
    if( keydict['w']){
        r->translCamFB(SNSTVTY);
    }
    if( keydict['s']){
        r->translCamFB(-SNSTVTY);
    }
    if( keydict['a']){
        r->translCamLR(SNSTVTY);
    }
    if( keydict['d']){
        r->translCamLR(-SNSTVTY);
    }
    if( keydict['q']){
        r->translCamUD(SNSTVTY);
    }
    if( keydict['e']){
        r->translCamUD(-SNSTVTY);
    }

    if( keydict['i']){
        r->rotateCamUD(10*SNSTVTY);
    }
    if( keydict['k']){
        r->rotateCamUD(-10*SNSTVTY);
    }
    if( keydict['j']){
        r->rotateCamLR(10*SNSTVTY);
    }
    if( keydict['l']){
        r->rotateCamLR(-10*SNSTVTY);
    }
    if( keydict['u']){
        r->rotateCamRoll(10*SNSTVTY);
    }
    if( keydict['o']){
        r->rotateCamRoll(-10*SNSTVTY);
    }


}

void keyup(unsigned char c, int x, int y){
    //printf("keyup: %c\n", c);
    keydict[c]=0;
}

void keydown(unsigned char c, int x, int y){
    //printf("keydown: %c\n", c);
    keydict[c]=1;
    switch(c){
        case 'r':
            for(int i = 0; i < numballs; i++)
            {
                balls[i].~Sphere();
            }

            for (int i = 0; i < numcons; i++)
            {
                constraints[i].~DistConstr();
            }

            ::operator delete (balls);
            ::operator delete (constraints);
			
			Read::readfile("config.txt");
            scene = Scene(balls, constraints, numballs, numcons);
            break;
        case 'x':
            exit(0);
            break;
		case 'b':
			Physics::setLimit(100);
			break;
		case 'n':
			Physics::setLimit(10);
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
