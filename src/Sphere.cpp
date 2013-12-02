#include "Sphere.h"
#include <cstdlib>
#include <ctime>

Sphere::Sphere(glm::detail::fvec4SIMD pos, glm::detail::fvec4SIMD vel){
	position = pos;
	oldPos = pos;
	velocity = vel;

	radius = 1;

    float r = (std::rand()%255)/255.0f;
    float g = (std::rand()%255)/255.0f;
    float b = (std::rand()%255)/255.0f;
    color = glm::vec4(r, g, b, 1);
}

Sphere::Sphere(double x, double y, double z){
	position = glm::detail::fvec4SIMD(x, y, z, 0.0f);
	oldPos = glm::detail::fvec4SIMD(x, y, z, 0.0f);
	velocity = glm::detail::fvec4SIMD(1+x/150., .4+y/130.,.3+z/110., 0.0f);

	radius = 1;

    float red = (std::rand()%255)/255.0f;
    float g = (std::rand()%255)/255.0f;
    float b = (std::rand()%255)/255.0f;
    color = glm::vec4(red,g,b,1);
}


Sphere::Sphere(double x, double y, double z, bool twoD){
	position = glm::detail::fvec4SIMD(x, y, z, 0.0f);
	oldPos = glm::detail::fvec4SIMD(x, y, z, 0.0f);
	if (!twoD)
		velocity = glm::detail::fvec4SIMD(1+x/15., 4+y/13.,3+z/11., 0.0f);
	else
		velocity = glm::detail::fvec4SIMD(1+x/15., 4+y/13., 0, 0.0f);

	radius = 1;

    float red = (std::rand()%255)/255.0f;
    float g = (std::rand()%255)/255.0f;
    float b = (std::rand()%255)/255.0f;
    color = glm::vec4(red,g,b,1);
}


Sphere::Sphere(double x, double y, double z, double r){
	position = glm::detail::fvec4SIMD(x, y, z, 0.0f);
	oldPos = glm::detail::fvec4SIMD(x, y, z, 0.0f);
	velocity = glm::detail::fvec4SIMD(1.0, 1.0, 1.0, 0.0f);

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

void Sphere::setPos(glm::detail::fvec4SIMD pos){
	position = pos;
}

void Sphere::setVelocity(glm::detail::fvec4SIMD vel){
	velocity = vel;
}

void Sphere::setOldPos(glm::detail::fvec4SIMD oldPosition){
	oldPos = oldPosition;
}

glm::detail::fvec4SIMD Sphere::getPos(){
	return position;
}

glm::detail::fvec4SIMD Sphere::getVelocity(){
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


glm::detail::fvec4SIMD Sphere::getOldPos(){
	return oldPos;
}

void Sphere::print(){
	printf("The coordinates are (%f,%f,%f) of radius %f\n",position.x,position.y,position.z,radius); 
}
