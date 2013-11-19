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
		glm::vec3 currPos = ball.getPos();
		glm::vec3 oldPos = ball.getOldPos();

		glm::vec3 newPos = glm::vec3(currPos.x + (currPos.x - oldPos.x) + acceli.x * t * t,
									 currPos.y + (currPos.y - oldPos.y) + acceli.y * t * t,
									 currPos.z + (currPos.z - oldPos.z) + acceli.z * t * t);

		ball.setOldPos(currPos);
		ball.setPos(newPos);
	}
}

/* Elastic wall collisions approach */
void UpdateBallBoundaries(std::vector<Sphere *> &balls){
	/*  Update each ball to the new location  */
	for (int i = 0; i < balls.size(); i++){
		Sphere &ball = (*balls.at(i));
		glm::vec3 oldPos = ball.oldPos();
		glm::vec3 currPos = ball.getPos();

	   /*Checking for Walls */
		if (newPos.x > LIMIT){
			oldPos.x = newPos.x;
			newPos.x = 2 * LIMIT - newPos.x;
			//oldVl.x = -oldVl.x;
		}
		if (newPos.y > LIMIT){
			oldPos.y = newPos.y;
			newPos.y = 2 * LIMIT - newPos.y;
			//oldVl.y = -oldVl.y;
		}
		if (newPos.z > LIMIT){
			oldPos.z = newPos.z;
			newPos.z = 2 * LIMIT - newPos.z;
			//oldVl.z = -oldVl.z;
		}
		if (newPos.x < 0){
			oldPos.x = newPos.x - oldPos.x;
			newPos.x = -newPos.x;
			//oldVl.x = -oldVl.x;
		}
		if (newPos.y < 0){
			oldPos.y = newPos.y - oldPos.y;
			newPos.y = -newPos.y; //try 0 too for damping?
			//oldVl.y = -oldVl.y/2.0;
			//oldVl.x = oldVl.x * .8;
			//oldVl.z = oldVl.z * .8;

		}
		if (newPos.z < 0){
			oldPos.z = newPos.z - oldPos.z;
			newPos.z = -newPos.z;
			//oldVl.z = -oldVl.z;
		}
	
	ball.setPos(newPos);
	//ball.setVelocity(oldVl);
	}
}


std::vector<Intersection *> getCollisions(std::vector <Sphere *> &balls){
	std::vector<Intersection *> intersects;
	std::vector <Sphere *> list_of_balls[GRID_SIZE * GRID_SIZE];
	for(int i = 0; i < balls.size(); i++){
		Sphere &s = *balls.at(i);
		int x = s.getPos().x / (100/GRID_SIZE);
		x = std::min(std::max(x,0),GRID_SIZE-1);
		int z = s.getPos().z / (100/GRID_SIZE);
		z = std::min(std::max(z,0),GRID_SIZE-1);
		list_of_balls[x * GRID_SIZE + z].push_back(&s);
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
								if (dist < radiiDist-.001){ // .001 to avoid rounding error
									intersects.push_back(new Intersection(list_of_balls[p1].at(b1), list_of_balls[p2].at(b2)));
								}
							}
						}
					}
				}		
			}
	}

	/* This is the non grided version
	for(int i = 1; i < balls.size(); i++){ //First compute all the intersections that happen
		for(int j = 0; j < i; j++){
			double dist = glm::distance((*balls.at(i)).getPos(), (*balls.at(j)).getPos());
			double radiiDist = (*balls.at(i)).getRadius() + (*balls.at(j)).getRadius();
			if (dist < radiiDist-.001){ // .001 to avoid rounding error
				intersects.push_back(new Intersection(balls.at(i),balls.at(j), dist, radiiDist));
			}
		}
	} */
	return intersects;
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
		s1Vel.y *= .9;
		s2Vel.y *= .9;
		s1.setVelocity(s2Vel);
		s2.setVelocity(s1Vel);
		delete iptr;
	}
}



//handled by Init.cpp. Prep for removal
/*
std::vector<DistConstr*> distanceConstrInit(std::vector<Sphere*> &balls){
  std::vector<DistConstr*> constraints;

  //naive O(n^2) comparisons
  for(int i = 0; i < balls.size(); i++){
    for (int j = i+1; j < balls.size(); j++){
      Sphere* s1 = balls.at(i);
      Sphere* s2 = balls.at(j);

      double dist = glm::distance((*s1).getPos(), (*s2).getPos());

      if(dist - (*s1).getRadius() - (*s2).getRadius() < .01){
        constraints.push_back(new DistConstr(s1, s2, dist));
      }
    }
  }

  return constraints;
}
*/

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
