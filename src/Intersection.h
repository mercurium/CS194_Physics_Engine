#pragma once
#include "Sphere.h"

class Intersection {
	Sphere *s1,*s2;

    public:
		Intersection(Sphere *s1, Sphere *s2);
        virtual ~Intersection ();
	
		Sphere * getS1();
		Sphere * getS2();
		void print();
    private:
        /* data */
};
