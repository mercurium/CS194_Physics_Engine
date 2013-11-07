#include "Render.h"
#include "Transform.h"
#include <stdio.h>
#include <string>
#include <cstring>
#include <vector>

void pr(glm::vec3& v){
   printf("<%.3f %.3f %.3f>",v[0],v[1],v[2]); 
}

void prmat(glm::mat4& m){
    std::string s("%.2f\t"); 
    std::string format = s+s+s+s+"\n"+s+s+s+s+"\n"+s+s+s+s+"\n"+s+s+s+s+"\n";
    char* cstr = new char[format.length()+1];
    std::strcpy(cstr, format.c_str());
   printf( cstr, m[0][0],m[0][1],m[0][2],m[0][3],
                  m[1][0],m[1][1],m[1][2],m[1][3],
                  m[2][0],m[2][1],m[2][2],m[2][3],
                  m[3][0],m[3][1],m[3][2],m[3][3]);
}

Render::Render (){
    camCenter = glm::vec3(0,0,4);
    camView = glm::vec3(0,0,-1);;
    camUp = glm::vec3(0,1,0);;
    zN = 0.1;
    zF = 100.0;
    fov = 60;
    
}

Render::~Render (){

}

void Render::draw(std::vector<Sphere*> spheres){

    loadCamMatrix( camCenter, camUp, camView);
    
    for(int i=0; i< spheres.size() ;i++){
        Sphere* sph = spheres[i];
        draw(*sph);
    }
}

void Render::drawtest(){
    printf("drawing!\n");
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
    
    //glTranslatef(0.0f,0.0f,-3.0f);
    /*
    glBegin(GL_TRIANGLES);
        glColor3f(1,0,0);
        glVertex3f(1.0f,0.0f,0.0f);
        glVertex3f(0.0f,1.0f,0.0f);
        glColor3f(0,0,1);
        glVertex3f(0.0f,0.0f,0.0f);
    glEnd();
    */
    glColor3f(1,0,0);
    Sphere sph(1,0,0);
    draw(sph);

    Sphere sph1(5,0,0);
    draw(sph1);

    Sphere sph2(0,2,0);
    draw(sph2);
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
