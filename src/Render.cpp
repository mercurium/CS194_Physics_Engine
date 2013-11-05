#include "Render.h"


Render::Render (){
    camCenter = glm::vec3(0,0,0);
    camView = glm::vec3(1,0,0);;
    camUp = glm::vec3(0,1,0);;
    zN = 0.1;
    zF = 100.0;
    aspect = 4.0/3.0;
    fov = 60;
    
}

Render::~Render (){

}

void Render::draw(Scene& scene){
    //Push Cam Matrix
    glm::mat4 cam = getCamMatrix( camCenter, camUp, camView, zN, zF, aspect, fov);
    push_glm_matrix( cam);
    
    /*
    for sph in Scene.getSpheres():
        draw( sph)
    */

    glPopMatrix();
}

void Render::draw(Sphere& sph){
    glm::vec3 center = sph.getPos();
    double rad = sph.getRadius();

    //Push translation by center
    push_glm_matrix( translate(center));

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
