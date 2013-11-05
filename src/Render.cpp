#include "Render.h"
#include <stdio.h>


Render::Render (){
    camCenter = glm::vec3(0,0,-3);
    camView = glm::vec3(0,0,1);;
    camUp = glm::vec3(0,1,0);;
    zN = 0.1;
    zF = 100.0;
    fov = 60;
    
}

Render::~Render (){

}

void Render::draw(Scene& scene){
    //Push Cam Matrix
    //loadCamMatrix( camCenter, camUp, camView, zN, zF, aspect, fov);
    
    /*
    for sph in Scene.getSpheres():
        draw( sph)
    */

    //glPopMatrix();
}

void Render::drawtest(){
    printf("drawing!\n");
    //loadCamMatrix( camCenter, camUp, camView);
    glTranslatef(0.0f,0.0f,-3.0f);
    glBegin(GL_TRIANGLES);
        glColor3f(1,0,0);
        glVertex3f(1.0f,0.0f,0.0f);
        glVertex3f(0.0f,1.0f,0.0f);
        glColor3f(0,0,1);
        glVertex3f(0.0f,0.0f,0.0f);
    glEnd();

    //glPopMatrix();
}

void Render::draw(Sphere& sph){
    glm::vec3 center = sph.getPos();
    double rad = sph.getRadius();
    glColor3f(1,0,0);

    //Push translation by center
    //push_glm_matrix( translate(center));
    glPushMatrix();
    glTranslatef(center[0],center[1],center[2]);

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
    glm::mat4 mat = rotate(camUp, deg);    
    camView = applyTransform(camView, mat);
}

void Render::rotateCamRoll(double deg){
    //Rotate up around view
    glm::mat4 mat = rotate(camView, deg);    
    camUp = applyTransform(camUp, mat);
}

void Render::translCam(glm::vec3& dist){
    Render::camCenter += dist;
}

glm::mat4 Render::getPerspective(float aspect){
    return glm::perspective((float)fov, aspect, (float)zN, (float)zF);
}
