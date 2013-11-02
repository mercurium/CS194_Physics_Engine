#include "Sphere.h"

Sphere::Sphere(double x, double y, double z){
	position = glm::vec3(x, y, z);
	velocity = glm::vec3(0.0, 0.0, 0.0);
	acceleration = glm::vec3(0.0, 0.0, 0.0);

	double radius = 1;
	double mass = 1;
}

Sphere::Sphere(double x, double y, double z, double r, double m){
	position = glm::vec3(x, y, z);
	velocity = glm::vec3(0.0, 0.0, 0.0);
	acceleration = glm::vec3(0.0, 0.0, 0.0);

	double radius = r;
	double mass = m;
}

Sphere::~Sphere (){
	delete position;
	delete radius;
	delete mass;
	delete velocity;
	delete acceleration;

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