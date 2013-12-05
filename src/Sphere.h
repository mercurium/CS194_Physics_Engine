#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/simd_vec4.hpp>

class Helper{
	glm::vec4 color;
	glm::simdVec4 oldPos;

	public:
		Helper(glm::vec4 colors, glm::simdVec4 oldPosition); 
		void setOldPos(glm::simdVec4 oldPosition);
		void setColor(glm::vec4 col);
		
		glm::simdVec4 getOldPos();
		glm::vec4 getColor();
};

class Sphere{
	glm::simdVec4 position;
	glm::simdVec4 velocity;

	double radius;
	Helper * helper;
	
	public:
		Sphere(glm::simdVec4 pos, glm::simdVec4 vel);
		Sphere(double x, double y, double z);
		Sphere(double x, double y, double z, bool twoD);
		Sphere(double x, double y, double z, double r);
		virtual ~Sphere(); 
		
		void setPos(glm::simdVec4 pos);
		void setOldPos(glm::simdVec4 oldPosition);
		void setVelocity(glm::simdVec4 vel);
		void setColor(glm::vec4 col);
		
		glm::simdVec4 getPos();
		glm::simdVec4 getOldPos();
		glm::simdVec4 getVelocity();
		glm::vec4 getColor();
		
		double getRadius();
		void print();
};

