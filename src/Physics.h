#pragma once
#include <vector>
#include "Intersection.h"
#include "Sphere.h"
#include "DistConstr.h"
#include "variables.h"

namespace Physics{
		void resolveCollisions(Intersection** intersections, int num_collisions);
		void UpdateBallPositions(Sphere* balls, int num_balls, double t);
		void UpdateBallBoundaries(Sphere* balls, int num_balls);
		void handleDistanceConstr(DistConstr* constraints, int constr_size);
		void setLimit(int n);

}
