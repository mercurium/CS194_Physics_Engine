#pragma once
#include "Sphere.h"

class Intersection {
    public:
        Intersection();
		Intersection(Sphere *s1, Sphere *s2, double dist);
        virtual ~Intersection ();
		Sphere s1,s2;
		double distance;
    private:
        /* data */
};
