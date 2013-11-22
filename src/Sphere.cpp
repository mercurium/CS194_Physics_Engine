#include "Sphere.h"
#include <cstdlib>
#include <ctime>

Sphere::Sphere(glm::vec3 pos, glm::vec3 vel){
	position = pos;
	oldPos = glm::vec3(pos.x, pos.y, pos.z);
	velocity = vel;

	radius = 1;

    float r = (std::rand()%255)/255.0f;
    float g = (std::rand()%255)/255.0f;
    float b = (std::rand()%255)/255.0f;
    color = glm::vec4(r, g, b, 1);
}

Sphere::Sphere(double x, double y, double z){
	position = glm::vec3(x, y, z);
	oldPos = glm::vec3(x, y, z);
	velocity = glm::vec3(1+x/150., .4+y/130.,.3+z/110.);

	radius = 1;

    float red = (std::rand()%255)/255.0f;
    float g = (std::rand()%255)/255.0f;
    float b = (std::rand()%255)/255.0f;
    color = glm::vec4(red,g,b,1);
}


Sphere::Sphere(double x, double y, double z, bool twoD){
	position = glm::vec3(x, y, z);
	oldPos = glm::vec3(x, y, z);
	if (!twoD)
		velocity = glm::vec3(1+x/15., 4+y/13.,3+z/11.);
	else
		velocity = glm::vec3(1+x/15., 4+y/13., 0);

	radius = 1;

    float red = (std::rand()%255)/255.0f;
    float g = (std::rand()%255)/255.0f;
    float b = (std::rand()%255)/255.0f;
    color = glm::vec4(red,g,b,1);
}


Sphere::Sphere(double x, double y, double z, double r){
	position = glm::vec3(x, y, z);
	oldPos = glm::vec3(x, y, z);
	velocity = glm::vec3(1.0, 1.0, 1.0);

	radius = r;

    float red = (std::rand()%255)/255.0f;
    float g = (std::rand()%255)/255.0f;
    float b = (std::rand()%255)/255.0f;
    color = glm::vec4(red,g,b,1);
}

Sphere::~Sphere (){
    /*
	delete position;
	delete radius;
	delete velocity;
    */
}

void Sphere::setPos(glm::vec3 pos){
	position = pos;
}

void Sphere::setVelocity(glm::vec3 vel){
	velocity = vel;
}


void Sphere::setOldPos(glm::vec3 oldPosition){
	oldPos = oldPosition;
}

glm::vec3 Sphere::getPos(){
	return position;
}

glm::vec3 Sphere::getVelocity(){
	return velocity;
}

glm::vec4 Sphere::getColor(){
	return color;
}

void Sphere::setColor(glm::vec4 col){
	color = col;
}

double Sphere::getRadius(){
	return radius;
}


glm::vec3 Sphere::getOldPos(){
	return oldPos;
}

void Sphere::print(){
	printf("The coordinates are (%f,%f,%f) of radius %f\n",position.x,position.y,position.z,radius); 
}


bool Sphere::operator == (const Sphere& s) const {
	return position == s.position;
}
