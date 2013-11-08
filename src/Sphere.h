#pragma once
#include <glm/glm.hpp>

class Sphere{
	glm::vec3 position;
	glm::vec3 oldPos;
	glm::vec3 velocity;
	glm::vec3 acceleration;

	double radius;
	double mass;
	
	public:
		Sphere(double x, double y, double z);
		Sphere(double x, double y, double z, double r, double m);
		virtual ~Sphere(); 
		
		void setPos(glm::vec3 pos);
		void setOldPos(glm::vec3 oldPosition);
		void setVelocity(glm::vec3 vel);
		void setAcceleration(glm::vec3 acc);
		
		glm::vec3 getPos();
		glm::vec3 getVelocity();
		glm::vec3 getAcceleration();
		double getRadius();
		double getMass();
		glm::vec3 getOldPos();

		bool operator == (const Sphere& s) const;
};
