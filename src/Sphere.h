#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/simd_vec4.hpp>

class Helper{
	glm::vec4 color;
	glm::detail::fvec4SIMD oldPos;

	public:
		Helper(glm::vec4 colors, glm::detail::fvec4SIMD oldPosition); 
		void setOldPos(glm::detail::fvec4SIMD oldPosition);
		void setColor(glm::vec4 col);
		
		glm::detail::fvec4SIMD getOldPos();
		glm::vec4 getColor();
		



};
class Sphere{
	glm::detail::fvec4SIMD position;
	glm::detail::fvec4SIMD velocity;

	double radius;
	Helper * helper;
	
	public:
		Sphere(glm::detail::fvec4SIMD pos, glm::detail::fvec4SIMD vel);
		Sphere(double x, double y, double z);
		Sphere(double x, double y, double z, bool twoD);
		Sphere(double x, double y, double z, double r);
		virtual ~Sphere(); 
		
		void setPos(glm::detail::fvec4SIMD pos);
		void setOldPos(glm::detail::fvec4SIMD oldPosition);
		void setVelocity(glm::detail::fvec4SIMD vel);
		void setColor(glm::vec4 col);
		
		glm::detail::fvec4SIMD getPos();
		glm::detail::fvec4SIMD getOldPos();
		glm::detail::fvec4SIMD getVelocity();
		glm::vec4 getColor();
		
		double getRadius();
		void print();
};

