#pragma once
#include <glm/glm.hpp>

class Sphere{
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;

	double radius;
	double mass;
	
	public:
		Sphere(double x, double y, double z);
		Sphere(double x, double y, double z, double r, double m);
		virtual ~Sphere(); 
		
		void setPos(double x, double y, double z);
		void setVelocity(double v_x, double v_y, double v_z);
		
		glm::vec3 getPos();
		glm::vec3 getVelocity();
		glm::vec3 getAcceleration();
		double getRadius();
		double getMass();
};