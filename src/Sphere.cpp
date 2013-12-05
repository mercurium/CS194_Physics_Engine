#include "Sphere.h"
#include <cstdlib>
#include <ctime>

Sphere::Sphere(glm::vec3 pos, glm::vec3 vel){
	position = pos;
	velocity = vel;

	radius = 1;

    float r = (std::rand()%255)/255.0f;
    float g = (std::rand()%255)/255.0f;
    float b = (std::rand()%255)/255.0f;
    glm::vec4 color(r, g, b, 1);
    helper = new Helper(color, pos);
}

Sphere::Sphere(double x, double y, double z){
	position = glm::vec3(x, y, z);
    glm::vec3 oldPos = glm::vec3(x, y, z);
	velocity = glm::vec3(1+x/150., .4+y/130.,.3+z/110.);

	radius = 1;

    float red = (std::rand()%255)/255.0f;
    float g = (std::rand()%255)/255.0f;
    float b = (std::rand()%255)/255.0f;
    glm::vec4 color(red,g,b,1);

    helper = new Helper(color, oldPos);
}


Sphere::Sphere(double x, double y, double z, bool twoD){
	position = glm::vec3(x, y, z);
    glm::vec3 oldPos = glm::vec3(x, y, z);
	if (!twoD)
		velocity = glm::vec3(1+x/15., 4+y/13.,3+z/11.);
	else
		velocity = glm::vec3(1+x/15., 4+y/13., 0);

	radius = 1;

    float red = (std::rand()%255)/255.0f;
    float g = (std::rand()%255)/255.0f;
    float b = (std::rand()%255)/255.0f;
    glm::vec4 color(red,g,b,1);
    helper = new Helper(color, oldPos);
}


Sphere::Sphere(double x, double y, double z, double r){
	position = glm::vec3(x, y, z);
    glm::vec3 oldPos = glm::vec3(x, y, z);
	velocity = glm::vec3(1.0, 1.0, 1.0);

	radius = r;

    float red = (std::rand()%255)/255.0f;
    float g = (std::rand()%255)/255.0f;
    float b = (std::rand()%255)/255.0f;
    glm::vec4 color(red,g,b,1);
    helper = new Helper(color, oldPos);
}

Sphere::~Sphere (){
    /*
	delete position;
	delete radius;
	delete velocity;
    */
    delete helper;
}

void Sphere::setPos(glm::vec3 pos){
	position = pos;
}

void Sphere::setVelocity(glm::vec3 vel){
	velocity = vel;
}

void Sphere::setOldPos(glm::vec3 oldPosition){
	//oldPos = oldPosition;
    helper->setOldPos(oldPosition);
}

glm::vec3 Sphere::getPos(){
	return position;
}

glm::vec3 Sphere::getVelocity(){
	return velocity;
}

glm::vec4 Sphere::getColor(){
	return helper->getColor();
}

void Sphere::setColor(glm::vec4 col){
	//color = col;
    helper->setColor(col);
}

double Sphere::getRadius(){
	return radius;
}


glm::vec3 Sphere::getOldPos(){
	return helper->getOldPos();
}

void Sphere::print(){
	printf("The coordinates are (%f,%f,%f) of radius %f\n", position.x, position.y, position.z, radius); 
}


Helper::Helper(glm::vec4 colors, glm::vec3 oldPosition){
    color = colors;
    oldPos = oldPosition;
}

void Helper::setOldPos(glm::vec3 oldPosition){
    oldPos = oldPosition;
}
void Helper::setColor(glm::vec4 col){
    color = col;
}
glm::vec3 Helper::getOldPos(){
    return oldPos;
}
glm::vec4 Helper::getColor(){
    return color;
}
