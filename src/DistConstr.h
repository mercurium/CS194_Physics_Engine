
#pragma once
#include "Sphere.h"

class DistConstr{
    public:
        DistConstr(void);
        ~DistConstr(void);

    private:
        Sphere *sphere1, *sphere2;
        double dist;

};
