#pragma once
#include "Sphere.h"

class Intersection {
	Sphere *s1,*s2;
	double dist, radiiDist;

    public:
		Intersection(Sphere *s1, Sphere *s2, double dist, double radiiDistance);
        virtual ~Intersection ();
	
		Sphere * getS1();
		Sphere * getS2();
		double getDist();
		double getRadiiDist();
    private:
        /* data */
};
