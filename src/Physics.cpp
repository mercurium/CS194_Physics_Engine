#include "Physics.h"
#include <stdio.h>

int LIMIT = 100;
int GRID_SIZE = 100;
glm::vec3 acceli = glm::vec3(0,-9.8,0);

namespace  Physics{

void UpdateBallPositions(std::vector<Sphere *> &balls, double t){
	/*  Update each ball to the new location  */
	for (int i = 0; i < balls.size(); i++){
		Sphere &ball = (*balls.at(i));
		glm::vec3 oldPos = ball.getOldPos();
		glm::vec3 pos = ball.getPos();

		glm::vec3 newPos = glm::vec3(pos.x * 2 - oldPos.x + t*t*acceli.x,
									pos.y * 2 - oldPos.y + t*t*acceli.y,
									pos.z * 2 - oldPos.z + t*t*acceli.z);
		ball.setOldPos(oldPos);
		ball.setPos(newPos);
	}

}

void UpdateBallBoundaries(std::vector<Sphere *> &balls){

	/*  Update each ball to the new location  */
	for (int i = 0; i < balls.size(); i++){
		Sphere &ball = (*balls.at(i));
		glm::vec3 oldVl = ball.getVelocity();
		glm::vec3 newPos = ball.getPos();
		glm::vec3 oldPos = ball.getOldPos();

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
			newPos.y = 0;
			oldVl.y = -oldVl.y/2.0;
			oldVl.x = oldVl.x * .9;
			oldVl.z = oldVl.z * .9;

		}
		if (newPos.z < 0){
			newPos.z = -newPos.z;
			oldVl.z = -oldVl.z;
		}
	ball.setPos(newPos);
	ball.setVelocity(oldVl);

	}

}

void resolveCollisions(std::vector<Intersection *> intersections){
	double dist, radiiDist;
	while(intersections.size() != 0)
	{
		Intersection * iptr = intersections.back();
		Intersection i = *iptr;
		intersections.pop_back();
		Sphere &s1 = *i.getS1(), &s2 = *i.getS2();
		glm::vec3 s1Pos = s1.getPos();
		glm::vec3 s2Pos = s2.getPos();
		
		dist = glm::distance(s1Pos,s2Pos);
		radiiDist = s1.getRadius() + s2.getRadius();

		glm::vec3 s1NewPos = glm::vec3( //Get rid of divide by 0 errors!
		   s1Pos.x + (s1Pos.x - s2Pos.x) * (radiiDist - dist)/ (2*dist),
	 	   s1Pos.y + (s1Pos.y - s2Pos.y) * (radiiDist - dist)/ (2*dist),
		   s1Pos.z + (s1Pos.z - s2Pos.z) * (radiiDist - dist)/ (2*dist));
		glm::vec3 s2NewPos = glm::vec3(
		   s2Pos.x + (s2Pos.x - s1Pos.x) * (radiiDist - dist)/ (2*dist),
		   s2Pos.y + (s2Pos.y - s1Pos.y) * (radiiDist - dist)/ (2*dist),
		   s2Pos.z + (s2Pos.z - s1Pos.z) * (radiiDist - dist)/ (2*dist));

		s1.setPos(s1NewPos);
		s2.setPos(s2NewPos);
		glm::vec3 s1Vel = s1.getVelocity();
		glm::vec3 s2Vel = s2.getVelocity();
		s1.setVelocity(glm::vec3(s2Vel.x*.7, s2Vel.y * .7, s2Vel.z * .7));
		s2.setVelocity(glm::vec3(s1Vel.x*.7, s1Vel.y * .7, s1Vel.z * .7));
		delete iptr;
	}
}


void handleDistanceConstr(std::vector<DistConstr*> &constraints){
  for (int i = 0; i < constraints.size(); i++)
  {
    DistConstr* constr = constraints.at(i);

    Sphere *s1 = (*constr).getBall(1);
    Sphere *s2 = (*constr).getBall(2);

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

void setLimit(int n){
	LIMIT = n;
}  

}
