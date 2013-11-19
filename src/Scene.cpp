#include "Scene.h"


Scene::Scene(){
	numBalls = 1000;
	twoD = false;
    GRID_SIZE = 100;
	balls = makeTestScene();
}

std::vector <Sphere *> Scene::makeTestScene(){
	std::vector <Sphere *> ballList;
	double x,y,z;
	for (int i = 0; i < this->numBalls; i++){
		x = ((i*i + 3*i+504)%2011 + i/200.)/10.;
		y = ((2*i*i - i + 1017)%2011 + i/200.)/10.;
		if (!this->twoD)
			z = ((5*i*i - 13 *i + 1014) % 2011 + i/200.)/10.;
		else
			z = 0;
		ballList.push_back(new Sphere(x,y,z,this->twoD));

	}
	return ballList;
}

void Scene::addBalls(){
	for (int i = 0; i < 100; i++){
		this->balls.push_back(new Sphere(10 * (i/10), 100, 10* (i%10), this->twoD));
	}
}

void Scene::UpdateScene(double time){
    Physics::UpdateBallPositions((this->balls), time);
    Physics::UpdateBallBoundaries(this->balls);
    //std::vector <Intersection *> intersections = Physics::getCollisions(*(&this->balls));
    std::vector <Intersection *> intersections = getCollisions();
    while (intersections.size()  != 0){
        Physics::resolveCollisions((intersections));
        intersections = getCollisions();
        //intersections = Physics::getCollisions(this->balls);
    }
	Physics::UpdateBallBoundaries(this->balls);
}

std::vector <Sphere *> Scene::getBalls(){
	return this->balls;
}

std::vector<Intersection *> Scene::getCollisions(){
	std::vector<Intersection *> intersects;

	std::vector <Sphere *> list_of_balls[GRID_SIZE * GRID_SIZE];
	for(int i = 0; i < balls.size(); i++){
		Sphere *s = balls.at(i);
		int x = s->getPos().x / (100/GRID_SIZE);
		x = std::min(std::max(x,0),GRID_SIZE-1);
		int z = s->getPos().z / (100/GRID_SIZE);
		z = std::min(std::max(z,0),GRID_SIZE-1);
		list_of_balls[x * GRID_SIZE + z].push_back(s);
	}


	for (int i = 0; i < GRID_SIZE; i++){
		for(int ii = 0; ii <= 1; ii++){
			if (i+ii < 0 || i+ii >= GRID_SIZE){ continue; }


			for (int j = 0; j < GRID_SIZE; j++){
					for (int jj = 0; jj <= 1; jj++){
						if (jj+j < 0 || jj+j >= GRID_SIZE){ continue; }

						int p1 = GRID_SIZE * i + j, p2 = GRID_SIZE * (i+ii) + j + jj;

						for(int b1 = 0; b1 < list_of_balls[p1].size(); b1++){
							for(int b2 = 0; b2 < list_of_balls[p2].size(); b2++){
								if (p1 == p2 && b1 <= b2){ continue; }
								
								double dist = glm::distance((*list_of_balls[p1].at(b1)).getPos(), (*list_of_balls[p2].at(b2)).getPos());
								double radiiDist = (*list_of_balls[p1].at(b1)).getRadius() + (*list_of_balls[p2].at(b2)).getRadius();
								if (dist < radiiDist-.0001){ // .001 to avoid rounding error
									intersects.push_back(new Intersection(list_of_balls[p1].at(b1), list_of_balls[p2].at(b2)));
								}
							}
						}
					}
				}		
			}
    }
    /*
	std::vector<Intersection *> intersects;
	for(int i = 1; i < balls.size(); i++){ //First compute all the intersections that happen
		for(int j = 0; j < i; j++){
			double dist = glm::distance(balls.at(i)->getPos(), balls.at(j)->getPos());
			double radiiDist = balls.at(i)->getRadius() + balls.at(j)->getRadius();
			if (dist < radiiDist-.001){ // .001 to avoid rounding error
				intersects.push_back(new Intersection(balls.at(i),balls.at(j)));
			}
		}
	}
    */
    return intersects;
}

  
