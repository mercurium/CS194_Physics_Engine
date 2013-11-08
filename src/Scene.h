#pragma once
#include <vector>
#include "Intersection.h"
#include "Sphere.h"
#include "DistConstr.h"

namespace Scene{
        std::vector<Intersection *> getCollisions(std::vector <Sphere *> &balls);
        void resolveCollisions(std::vector <Sphere *> &balls);
        void UpdateBallPositions(std::vector <Sphere *> &balls);
        void UpdateScene(std::vector <Sphere *> &balls);
		std::vector<Sphere *>  makeTestScene();

};
