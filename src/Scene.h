#pragma once
#include <vector>
#include "Intersection.h"
#include "Sphere.h"


class Scene{
    public:
        Scene(void);
        ~Scene(void);
        std::vector<Intersection> getIntersections(Sphere &obj);

    private:
        std::vector<Sphere *> balls;
        std::vector<DistConstr *> distContraints;

};
