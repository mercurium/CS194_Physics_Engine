#include "Sphere.h"

Sphere::Sphere(double x, double y, double z){
	position = glm::vec3(x, y, z);
	oldPos = glm::vec3(x, y, z);
	velocity = glm::vec3(1.0, 1.0, 1.0);
	acceleration = glm::vec3(0.0, 0.0, 0.0);

	radius = 1;
	mass = 1;
}

Sphere::Sphere(double x, double y, double z, double r, double m){
	position = glm::vec3(x, y, z);
	oldPos = glm::vec3(x, y, z);
	velocity = glm::vec3(1.0, 1.0, 1.0);
	acceleration = glm::vec3(0.0, 0.0, 0.0);

	radius = r;
	mass = m;
}

Sphere::~Sphere (){
    /*
	delete position;
	delete radius;
	delete mass;
	delete velocity;
	delete acceleration;
    */
}

void Sphere::setPos(glm::vec3 pos){
	position = pos;
}

void Sphere::setVelocity(glm::vec3 vel){
	velocity = vel;
}

void Sphere::setAcceleration(glm::vec3 acc){
	acceleration = acc;
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

glm::vec3 Sphere::getAcceleration(){
	return acceleration;
}

double Sphere::getRadius(){
	return radius;
}

double Sphere::getMass(){
	return mass;
}

glm::vec3 Sphere::getOldPos(){
	return oldPos;
}


bool Sphere::operator == (const Sphere& s) const {
	return position == s.position;
}
