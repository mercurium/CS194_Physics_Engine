#include "Sphere.h"
#include <cstdlib>
#include <ctime>


Sphere::Sphere(glm::simdVec4 pos, glm::simdVec4 vel){
	position = pos;
	velocity = vel;
	radius = 1;

    float r = (std::rand()%255)/255.0f;
    float g = (std::rand()%255)/255.0f;
    float b = (std::rand()%255)/255.0f;
    glm::vec4 color = glm::vec4(r,g,b,1);
	glm::simdVec4 oldPos = pos;
	helper = new Helper(color, oldPos);
}

Sphere::Sphere(double x, double y, double z){
	position = glm::detail::fvec4SIMD(x, y, z, 0.0f);
	velocity = glm::detail::fvec4SIMD(0.0f, 1+x/150., .4+y/130.,.3+z/110.);

	radius = 1;

    float red = (std::rand()%255)/255.0f;
    float g = (std::rand()%255)/255.0f;
    float b = (std::rand()%255)/255.0f;
    glm::vec4 color = glm::vec4(red,g,b,1);
	glm::simdVec4 oldPos = glm::detail::fvec4SIMD(0.0f, x, y, z);
	helper = new Helper(color, oldPos);
}


Sphere::Sphere(double x, double y, double z, bool twoD){
	position = glm::detail::fvec4SIMD(x, y, z, 0.0f);
	if (!twoD)
		velocity = glm::detail::fvec4SIMD(0.0f, 1+x/15., 4+y/13.,3+z/11.);
	else
		velocity = glm::detail::fvec4SIMD(0.0f, 1+x/15., 4+y/13., 0);

	radius = 1;

    float red = (std::rand()%255)/255.0f;
    float g = (std::rand()%255)/255.0f;
    float b = (std::rand()%255)/255.0f;
    glm::vec4 color = glm::vec4(red,g,b,1);
	glm::simdVec4 oldPos = glm::detail::fvec4SIMD(0.0f, x, y, z);
	helper = new Helper(color, oldPos);
}


Sphere::Sphere(double x, double y, double z, double r){
	position = glm::detail::fvec4SIMD(0.0f, x, y, z);
	velocity = glm::detail::fvec4SIMD(0.0f, 1.0, 1.0, 1.0);

	radius = r;

    float red = (std::rand()%255)/255.0f;
    float g = (std::rand()%255)/255.0f;
    float b = (std::rand()%255)/255.0f;
    glm::vec4 color = glm::vec4(red,g,b,1);
	glm::simdVec4 oldPos = glm::detail::fvec4SIMD(0.0f, x, y, z);
	helper = new Helper(color, oldPos);
}

Sphere::~Sphere (){
    /*
	delete position;
	delete radius;
	delete velocity;
    */
}

void Sphere::setPos(glm::simdVec4 pos){
	position = pos;
}

void Sphere::setVelocity(glm::simdVec4 vel){
	velocity = vel;
}

void Sphere::setOldPos(glm::simdVec4 oldPosition){
	helper->setOldPos(oldPosition);
}

glm::simdVec4 Sphere::getPos(){
	return position;
}

glm::simdVec4 Sphere::getVelocity(){
	return velocity;
}

glm::vec4 Sphere::getColor(){
	return helper->getColor();
}

void Sphere::setColor(glm::vec4 col){
	helper->setColor(col);
}

double Sphere::getRadius(){
	return radius;
}


glm::simdVec4 Sphere::getOldPos(){
	return helper->getOldPos();
}

void Sphere::print(){
	glm::vec4 posVec4 = glm::vec4_cast(position);
	printf("The coordinates are (%f,%f,%f) of radius %f\n", posVec4.x, posVec4.y, posVec4.z, radius); 
}


Helper::Helper(glm::vec4 colors, glm::simdVec4 oldPosition){
	color = colors;
	oldPos = oldPosition;
}

void Helper::setOldPos(glm::simdVec4 pos){
	oldPos = pos;
}

void Helper::setColor(glm::vec4 col){
	color = col;
}

glm::simdVec4 Helper::getOldPos(){
	return oldPos;
}

glm::vec4 Helper::getColor(){
	return color;
}