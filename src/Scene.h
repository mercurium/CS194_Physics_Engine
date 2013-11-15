#pragma once
#include <vector>
#include "Intersection.h"
#include "Sphere.h"
#include "DistConstr.h"
#include "Physics.h"

class Scene{
		private:
		int numBalls;
			bool twoD;
			std::vector<Sphere *> balls;
			std::vector<DistConstr *> distConstr;

		public:
			Scene();
	        void UpdateScene(double time);
			std::vector<Sphere *> makeTestScene();
			std::vector<Sphere *> getBalls();
			std::vector <DistConstr *> makeTestDistConstr(std::vector <Sphere *> balls);

};
