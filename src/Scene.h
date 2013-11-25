#pragma once
#include "Intersection.h"
#include "Sphere.h"
#include "DistConstr.h"
#include "Physics.h"

class Scene{
		private:
			int numBalls;
			int numConstr;
			int numCollisions;
			bool twoD;
			int GRID_SIZE;
			int GRID_COL_SIZE;

			Sphere* balls;
			DistConstr* distConstr;
			virtual Intersection** getCollisions();

		public:
			Scene();
			Scene(Sphere* ballList, DistConstr* constraints, int ball_size, int constraints_size);
			void UpdateScene(double time);
			//std::vector<Sphere *> makeTestScene();
			//std::vector <DistConstr *> makeTestDistConstr(std::vector <Sphere *> balls);
			Sphere* getBalls();

};
