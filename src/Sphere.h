#pragma once
#include <glm/glm.hpp>

class Sphere{
	glm::vec3 position;
	glm::vec3 oldPos;
	glm::vec3 velocity;
    glm::vec4 color;

	double radius;
	double mass;
	
	public:
		Sphere(glm::vec3 pos, glm::vec3 vel);
		Sphere(double x, double y, double z);
		Sphere(double x, double y, double z, bool twoD);
		Sphere(double x, double y, double z, double r);
		virtual ~Sphere(); 
		
		void setPos(glm::vec3 pos);
		void setOldPos(glm::vec3 oldPosition);
		void setVelocity(glm::vec3 vel);
		
		glm::vec3 getPos();
		glm::vec4 getColor();
		glm::vec3 getVelocity();
		double getRadius();
		glm::vec3 getOldPos();
		void print();

		bool operator == (const Sphere& s) const;
};
