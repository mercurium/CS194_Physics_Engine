#include "Render.h"


Render::Render (){
    camCenter = glm::vec3(0,0,0);
    camView = glm::vec3(1,0,0);;
    camUp = glm::vec3(0,1,0);;
    
}

Render::~Render (){

}

void Render::draw(Scene& scene){
    //Push Cam Matrix
    /*
    for sph in Scene.getSpheres():
        draw( sph)
    */
}

void Render::draw(Sphere& sph){
    glm::vec3 center = sph.getPos();
    double rad = sph.getRadius();

    //Push translation matrix by center
    //glutSolidSphere( rad,50,50); 
    //Pop translation matrix
}

void Render::rotateCamUD(double deg){
    glm::vec3 right = glm::cross( camUp, camView);
    //Rotate Up and View around right

}

void Render::rotateCamLR(double deg){
    //Rotate view around Up

}

void Render::rotateCamRoll(double deg){
    //Rotate up around view

}

void Render::translCam(glm::vec3& dist){
    Render::camCenter += dist;
}
