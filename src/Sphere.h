#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/simd_vec4.hpp>

class Sphere{
	detail::fvec4SIMD position;
	detail::fvec4SIMD oldPos;
	detail::fvec4SIMD velocity;
    glm::vec4 color;

	double radius;
	double mass;
	
	public:
		Sphere(detail::fvec4SIMD pos, detail::fvec4SIMD vel);
		Sphere(double x, double y, double z);
		Sphere(double x, double y, double z, bool twoD);
		Sphere(double x, double y, double z, double r);
		virtual ~Sphere(); 
		
		void setPos(detail::fvec4SIMD pos);
		void setOldPos(detail::fvec4SIMD oldPosition);
		void setVelocity(detail::fvec4SIMD vel);
		void setColor(glm::vec4 col);
		
		detail::fvec4SIMD getPos();
		detail::fvec4SIMD getOldPos();
		detail::fvec4SIMD getVelocity();
		glm::vec4 getColor();
		
		double getRadius();
		void print();

		bool operator == (const Sphere& s) const;
};
