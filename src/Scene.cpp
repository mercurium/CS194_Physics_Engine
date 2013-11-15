#include "Scene.h"

Scene::Scene(){
	numBalls = 200;
	twoD = false;
	balls = makeTestScene();
	distConstr = makeTestDistConstr(balls);
}

std::vector <Sphere *> Scene::makeTestScene(){
	std::vector <Sphere *> ballList;
	double x,y,z;
	for (int i = 0; i < this->numBalls; i++){
		x = (i*i + 3*i+504)%211 + i/200.;
		y = (2*i*i - i + 1017)%211 + i/200.;
		if (!this->twoD)
			z = (5*i*i - 13 *i + 1014) % 211 + i/200.;
		else
			z = 0;
		ballList.push_back(new Sphere(x,y,z,this->twoD));

	}
	return ballList;
}

std::vector <DistConstr *> Scene::makeTestDistConstr(std::vector <Sphere *> balls){
	std::vector <DistConstr *> distConstr;
	for(int n = 0; n < balls.size() /4; n++){
		for(int i = 1; i < 4; i++){
			for (int j = 0; j < i; j++){
				distConstr.push_back(new DistConstr(balls.at(4*n+i),balls.at(4*n+j),3));
			}
		}
	}
	return distConstr;

}

void Scene::UpdateScene(double time){
	Physics::UpdateBallPositions(*(&this->balls), time);
	std::vector <Intersection *> intersections = Physics::getCollisions(*(&this->balls));
	Physics::handleDistanceConstr(*(&this->distConstr));
	while (intersections.size()  != 0){
		Physics::resolveCollisions(*(&intersections));
		Physics::handleDistanceConstr(this->distConstr);
		intersections = Physics::getCollisions(this->balls);
	}
	Physics::UpdateBallBoundaries(this->balls);
}

std::vector <Sphere *> Scene::getBalls(){
	return *(&this->balls);
}

  
