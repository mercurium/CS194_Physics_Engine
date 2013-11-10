#include <GL/glew.h>
#include <GL/glut.h>
#include "Render.h"
#include "Transform.h"
#include "Util.h"


Render::Render (){
    init(glm::vec3(0,0,0), glm::vec3(0,0,1), glm::vec3(0,1,0));
}

Render::Render (glm::vec3 center, glm::vec3 view, glm::vec3 up){
    init(center,view,up);
}

Render::~Render (){
    delete shader;
}

void Render::init (glm::vec3 center, glm::vec3 view, glm::vec3 up){
    camCenter = center;
    camView = view;
    camUp = up;
    zN = 0.1;
    zF = 200.0;
    fov = 60;
    shader = new Shader();    
}

void Render::draw(std::vector<Sphere*> spheres){

    loadCamMatrix( camCenter, camUp, camView);

    glUniform1i(shader->enablelighting, true); //enable lighting in shader
    GLfloat x = 300;
    int numlights = 2;
    glUniform1i(shader->numused, numlights);
    glm::vec4 selfpos( 0,0,-10,1);
    float lightPos[] = {0,40,-10,1,0,0,0,1};
    float lightColor[] = {1,1,1,1,0,0,0,1};
    glUniform4fv(shader->lightpos, numlights, lightPos);
    glUniform4fv(shader->lightcol, numlights, lightColor);
    glUniform4fv(shader->ambientcol, 1, &glm::vec4(.01,.01,.01,1)[0]);
    glUniform4fv(shader->specularcol, 1, &glm::vec4(1,1,1,1)[0]);
    glUniform4fv(shader->emissioncol, 1, &glm::vec4(0,0,0,1)[0]);
    glUniform1fv(shader->shininesscol, 1, &x);
    
    for(int i=0; i< spheres.size() ;i++){
        Sphere* sph = spheres[i];
        draw(*sph);
    }
}

void Render::drawtest(){
    printf("Drawing\n");
    //printf("cent: ");pr(camCenter);printf(" up:");pr(camUp);printf(" view:");pr(camView);printf("\n");
    /*
    glm::vec3 viewCenter = camCenter+camView; 
    //glm::mat4 lookAt(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up) {
    //glm::mat4 mv = glm::lookAt( viewCenter, camCenter, camUp);
    glm::mat4 mv = lookAt( camCenter, viewCenter, camUp);
    printf("LookAt:\n");
    prmat(mv);
    load_glm_matrix(mv);
    */

    loadCamMatrix( camCenter, camUp, camView);
    //glm::mat4 mv= getCamMatrix( camCenter, camUp, camView);

    printf("Drawing 2\n");
    glUniform1i(shader->enablelighting, true); //enable lighting in shader
    GLfloat x = 100;
    glUniform1i(shader->numused, 1);
    //glm::vec4 selfpos( camCenter[0],camCenter[1],camCenter[2],1);
    glm::vec4 selfpos( 6,0,0,1);
    glUniform4fv(shader->lightpos, 1, &selfpos[0]);
    glUniform4fv(shader->lightcol, 1, &glm::vec4(1,1,1,0)[0]);
    glUniform4fv(shader->ambientcol, 1, &glm::vec4(.01,.01,.01,1)[0]);
    glUniform4fv(shader->specularcol, 1, &glm::vec4(1,1,1,1)[0]);
    glUniform4fv(shader->emissioncol, 1, &glm::vec4(0,0,0,1)[0]);
    glUniform1fv(shader->shininesscol, 1, &x);
    
    glColor3f(1,0,0);
    Sphere sph(0,0,1);
    draw(sph);

    glColor3f(0,1,0);
    Sphere sph1(0,0,7);
    draw(sph1);

    glColor3f(0,0,1);
    Sphere sph2(0,0,13);
    draw(sph2);
    printf("Drawing 5\n");

    /*
    glPushMatrix();
    glTranslatef(1,0,0);
    glutSolidSphere( 1,50,50); 
    glPopMatrix();
    */

    //glPopMatrix();
}

void Render::draw(Sphere& sph){
    glm::vec3 center = sph.getPos();
    double rad = sph.getRadius();

    //Push translation by center
    glPushMatrix();
    glTranslatef(center[0],center[1],center[2]);

    //load color
    glm::vec4 color = sph.getColor();
    //glColor3f(color[0],color[1],color[2]);
    glUniform4fv(shader->diffusecol, 1, &color[0]);

    //Draw sphere
    glutSolidSphere( rad,50,50); 

    //Pop translation matrix
    glPopMatrix();
}

void Render::rotateCamUD(double deg){
    glm::vec3 right = glm::cross( camUp, camView);
    //Rotate Up and View around right
    glm::mat4 mat = rotate(right, deg);    
    camUp = applyTransform(camUp, mat);
    camView = applyTransform(camView, mat);
}

void Render::rotateCamLR(double deg){
    //Rotate view around Up
    glm::mat4 mat = rotate(camUp, -deg);    
    camView = applyTransform(camView, mat);
}

void Render::rotateCamRoll(double deg){
    //Rotate up around view
    glm::mat4 mat = rotate(camView, deg);    
    camUp = applyTransform(camUp, mat);
}

void Render::translCamFB(double dist){
    camCenter += ((float)dist)*camView;
}

void Render::translCamUD(double dist){
    camCenter += ((float)dist)*camUp;
}

void Render::translCamLR(double dist){
    glm::vec3 right = glm::cross( camUp, camView);
    camCenter += ((float)dist)*right;
}

glm::mat4 Render::getPerspective(float aspect){
    return glm::perspective((float)fov, aspect, (float)zN, (float)zF);
}
