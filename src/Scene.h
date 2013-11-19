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
            int GRID_SIZE;
            virtual std::vector<Intersection *> getCollisions();

		public:
			Scene();
	        void UpdateScene(double time);
			std::vector<Sphere *> makeTestScene();
			std::vector<Sphere *> getBalls();
			void addBalls();

};
