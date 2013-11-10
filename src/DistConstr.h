
#pragma once
#include "Sphere.h"

class DistConstr{
	Sphere* s1;
	Sphere* s2;

	double distance;

    public:
        DistConstr(Sphere* a, Sphere* b, double d);
        virtual ~DistConstr();
        Sphere* getBall(int i);
        double getDist();
        bool contains(Sphere* a);
        bool contains(Sphere* a, Sphere* b);
};