
#pragma once
#include "Sphere.h"

class DistConstr{
	Sphere* s1;
	Sphere* s2;

	double distance;

    public:
        DistConstr(Sphere* a, Sphere* b, double d);
        virtual ~DistConstr();
        double DistConstr::getDist();
        bool DistConstr::contains(Sphere* a, Sphere* b);
};