#pragma once
#include <vector>
#include "Intersection.h"
#include "Sphere.h"
#include "DistConstr.h"

namespace Scene{
        std::vector<Intersection *> getCollisions(std::vector <Sphere *> &balls);
        void resolveCollisions(std::vector <Intersection *> intersections);
        void UpdateBallPositions(std::vector <Sphere *> &balls, double t);
        void UpdateScene(std::vector <Sphere *> &balls, double t);
		std::vector<Sphere *>  makeTestScene();
		void handleDistanceConstr(std::vector<DistConstr*> &constraints);

};
