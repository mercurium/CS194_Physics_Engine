#include "Scene.h"

int LIMIT = 100;
int numBalls = 200;
bool twoD = false;

namespace  Scene{

void updateBallPositions(std::vector<Sphere *> &balls){
	/*  Update each ball to the new location  */
	for (int i = 0; i < balls.size(); i++){
		Sphere &ball = (*balls.at(i));
		glm::vec3 oldPos = ball.getPos();
		ball.setOldPos(oldPos);
		glm::vec3 oldVl = ball.getVelocity();
		glm::vec3 accel = ball.getAcceleration();
		glm::vec3 newPos = glm::vec3(oldPos.x + oldVl.x, oldPos.y + oldVl.y, oldPos.z + oldVl.z);


	   /*Checking for Walls */
		if (newPos.x > LIMIT){
			newPos.x = 2* LIMIT - newPos.x;
			oldVl.x = -oldVl.x;
		}
		if (newPos.y > LIMIT){
			newPos.y = 2* LIMIT - newPos.y;
			oldVl.y = -oldVl.y;
		}
		if (newPos.z > LIMIT){
			newPos.z = 2* LIMIT - newPos.z;
			oldVl.z = -oldVl.z;
		}
		if (newPos.x < 0){
			newPos.x = -newPos.x;
			oldVl.x = -oldVl.x;
		}
		if (newPos.y < 0){
			newPos.y = -newPos.y;
			oldVl.y = -oldVl.y/2;
			oldVl.x = oldVl.x * .8;
			oldVl.z = oldVl.z * .8;
		}
		if (newPos.z < 0){
			newPos.z = -newPos.z;
			oldVl.z = -oldVl.z;
		}
	oldVl.x += accel.x;
	oldVl.y += accel.y;
	oldVl.z += accel.z;
	
	ball.setPos(newPos);
	ball.setOldPos(oldPos);
	ball.setVelocity(oldVl);

	}

}

std::vector <Sphere *> makeTestScene(){
	std::vector <Sphere *> balls;
	double x,y,z;
	for (int i = 0; i < numBalls; i++){
		x = (i*i + 3*i+504)%211 + i/200.;
		y = (2*i*i - i + 1017)%211 + i/200.;
		if (!twoD)
			z = (5*i*i - 13 *i + 1014) % 211 + i/200.;
		else
			z = 0;
		balls.push_back(new Sphere(x,y,z,twoD));

	}
	return balls;

}

std::vector<Intersection *> getCollisions(std::vector <Sphere *> &balls){
	std::vector<Intersection *> intersects;
	for(int i = 1; i < balls.size(); i++){ //First compute all the intersections that happen
		for(int j = 0; j < i; j++){
			double dist = glm::distance((*balls.at(i)).getPos(), (*balls.at(j)).getPos());
			double radiiDist = (*balls.at(i)).getRadius() + (*balls.at(j)).getRadius();
			if (dist < radiiDist-.001){ // .001 to avoid rounding error
				intersects.push_back(new Intersection(balls.at(i),balls.at(j), dist, radiiDist));
			}

		}
	}
	return intersects;
}

void resolveCollisions(std::vector<Intersection *> intersections){
	double dist, radiiDist;
	while(intersections.size() != 0)
	{
		Intersection &i = *intersections.back();
		intersections.pop_back();
		Sphere &s1 = *i.getS1(), &s2 = *i.getS2();
		dist = i.getDist();
		radiiDist = i.getRadiiDist();

		glm::vec3 s1Pos = s1.getPos();
		glm::vec3 s2Pos = s2.getPos();
		glm::vec3 s1NewPos = glm::vec3( //Get rid of divide by 0 errors!
		   s1Pos.x + (s1Pos.x - s2Pos.x) * (radiiDist - dist)/ (2*dist+.0000001), 
	 	   s1Pos.y + (s1Pos.y - s2Pos.y) * (radiiDist - dist)/ (2*dist+.0000001),
		   s1Pos.z + (s1Pos.z - s2Pos.z) * (radiiDist - dist)/ (2*dist+.0000001));
		glm::vec3 s2NewPos = glm::vec3(
		   s2Pos.x + (s2Pos.x - s1Pos.x) * (radiiDist - dist)/ (2*dist+.0000001),
		   s2Pos.y + (s2Pos.y - s1Pos.y) * (radiiDist - dist)/ (2*dist+.0000001),
		   s2Pos.z + (s2Pos.z - s1Pos.z) * (radiiDist - dist)/ (2*dist+.0000001));
		s1.setPos(s1NewPos);
		s2.setPos(s2NewPos);
		glm::vec3 s1Vel = s1.getVelocity();
		s1.setVelocity(s2.getVelocity());
		s2.setVelocity(s1Vel);
	}
}

void UpdateScene(std::vector <Sphere *> &balls) {
	updateBallPositions(*(&balls));
	std::vector <Intersection *> intersections = getCollisions(balls);

	while (intersections.size()  != 0){
		resolveCollisions(intersections);
		intersections = getCollisions(balls);
	}

}

std::vector<DistConstr*> distanceConstrInit(std::vector<Sphere*> &balls){
  std::vector<DistConstr*> constraints;

  //naive O(n^2) comparisons
  for(int i = 0; i < balls.size(); i++){
    for (int j = i+1; j < balls.size(); j++){
      Sphere* s1 = balls.at(i);
      Sphere* s2 = balls.at(j);

      double dist = glm::distance((*s1).getPos(), (*s2).getPos());

      if(dist == (*s1).getRadius() + (*s2).getRadius()){
        constraints.push_back(new DistConstr(s1, s2, dist));
      }
    }
  }

  return contraints;
}

void handleDistanceConstr(std::vector<Sphere*> &balls, std::vector<DistConstr*> &constraints){
  for (int i = 0; i < contraints.size(); i++)
  {
    DistConstr* constr = constraints.at(i);

    Sphere s1 = (constr).getBall(1);
    Sphere s2 = (constr).getBall(2);

    double actual_dist = glm::distance((*s1).getPos(), (*s2).getPos());
    double constr_dist = (*constr).getDist();

    double diff = actual_dist - constr_dist;

    glm::vec3 s1Pos = (*s1).getPos();
    glm::vec3 s2Pos = (*s2).getPos();

    glm::vec3 s1NewPos = glm::vec3( //Get rid of divide by 0 errors!
     s1Pos.x + (s1Pos.x - s2Pos.x) * (diff)/(2*actual_dist+.0000001), 
     s1Pos.y + (s1Pos.y - s2Pos.y) * (diff)/(2*actual_dist+.0000001),
     s1Pos.z + (s1Pos.z - s2Pos.z) * (diff)/(2*actual_dist+.0000001));
    glm::vec3 s2NewPos = glm::vec3(
     s2Pos.x + (s2Pos.x - s1Pos.x) * (diff)/(2*actual_dist+.0000001),
     s2Pos.y + (s2Pos.y - s1Pos.y) * (diff)/(2*actual_dist+.0000001),
     s2Pos.z + (s2Pos.z - s1Pos.z) * (diff)/(2*actual_dist+.0000001));
    
    (*s1).setPos(s1NewPos);
    (*s2).setPos(s2NewPos);
  }

}
  
}