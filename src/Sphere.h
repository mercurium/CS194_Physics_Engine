#pragma once
#include <glm/glm.hpp>

class Sphere{
	glm::vec3 position;
	glm::vec3 oldPos;
	glm::vec3 velocity;
    glm::vec4 color;

	double radius;
	
	public:
		Sphere(glm::vec3 pos, glm::vec3 vel);
		Sphere(double x, double y, double z);
		Sphere(double x, double y, double z, bool twoD);
		Sphere(double x, double y, double z, double r);
		virtual ~Sphere(); 
		
		void setPos(glm::vec3 pos);
		void setOldPos(glm::vec3 oldPosition);
		void setVelocity(glm::vec3 vel);
		void setColor(glm::vec4 col);
		
		glm::vec3 getPos();
		glm::vec3 getOldPos();
		glm::vec3 getVelocity();
		glm::vec4 getColor();
		
		double getRadius();
		void print();
};
