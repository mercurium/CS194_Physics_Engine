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
			std::vector<DistConstr *> distConstr;
            int GRID_SIZE;

        protected:
            std::vector<Sphere *> balls;


		public:
			Scene();
			Scene(std::vector<Sphere *> ballList, std::vector <DistConstr *> constraints);
            void init(std::vector<Sphere *> ballList, std::vector <DistConstr *> constraints);
            virtual std::vector<Intersection *> getCollisions();
	        void UpdateScene(double time);
			std::vector<Sphere *> makeTestScene();
			std::vector <DistConstr *> makeTestDistConstr(std::vector <Sphere *> balls);
			std::vector<Sphere *> getBalls();

};
