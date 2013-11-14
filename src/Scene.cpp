#include "Scene.h"

Scene::Scene(){
	numBalls = 3000;
	twoD = false;
	balls = makeTestScene();
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

void Scene::UpdateScene(double time){
	Physics::UpdateBallPositions(*(&this->balls), time);
	
	std::vector <Intersection *> intersections = Physics::getCollisions(*(&this->balls));
	
	
	while (intersections.size()  != 0){
		Physics::resolveCollisions(*(&intersections));
		intersections = Physics::getCollisions(this->balls);
	}
	Physics::UpdateBallBoundaries(this->balls);
}

std::vector <Sphere *> Scene::getBalls(){
	return *(&this->balls);
}

  
