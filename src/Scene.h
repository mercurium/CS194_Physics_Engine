#pragma once
#include <vector>
#include "Intersection.h"
#include "Sphere.h"
#include "DistConstr.h"

class Scene{
    std::vector<Sphere *> balls;
    std::vector<DistConstr *> distContraints;
    public:
        Scene(void);
        ~Scene(void);
        std::vector<Intersection> getIntersections(Sphere &obj);
        void UpdateBallPositions();
        void UpdateScene();

    private:

};
