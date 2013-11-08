
#include "Scene.h"
using namespace std;
//Constructor
Scene::Scene(){ 

}

//Deconstructor
Scene::~Scene(){ 


}

std::vector<Intersection> Scene::getIntersections(Sphere &obj){
    //Geometry intersection routine
}

void updateBallPositions(vector<Sphere *> balls){
    /*  Update each ball to the new location  */
    for (int i = 00; i < balls.size(); i++){
       Sphere ball = *balls.at(i);
       glm::vec3 oldPos = ball.getPos();
       glm::vec3 oldVl = ball.getVelocity();
       glm::vec3 newPos = glm::vec3(oldPos.x + oldVl.x, oldPos.y + oldVl.y, oldPos.z + oldVl.z);
       ball.setPos(newPos);
    }

}

vector<Intersection *> getCollisions(vector <Sphere *> balls){
	vector<Intersection *> intersects;
    for(int i = 1; i < balls.size(); i++){ //First computer all the intersections that happen
        for(int j = 0; j < i; j++){
            Sphere s1 = *balls.at(i);
            Sphere s2 = *balls.at(j);
            double dist = glm::distance(s1.getPos(), s2.getPos());
            double radiiDist = s1.getRadius() + s2.getRadius();
            if (dist < radiiDist){
				intersects.push_back(new Intersection(s1,s2, radiiDist-dist));
			}

		}
	}
	return intersects;
}

void resolveCollisions(vector <Sphere *> balls){
    bool notDone = true, almostDone = true;
    while (notDone){
        for(int i = 1; i < balls.size(); i++){ //First computer all the intersections that happen
            for(int j = 0; j < i; j++){
                Sphere s1 = *balls.at(i);
                Sphere s2 = *balls.at(j);
                double dist = glm::distance(s1.getPos(), s2.getPos());
                double radiiDist = s1.getRadius() + s2.getRadius();
                if (dist < radiiDist){
                   glm::vec3 s1Pos = s1.getPos();
                   glm::vec3 s2Pos = s2.getPos();
                   glm::vec3 s1NewPos = glm::vec3(s1Pos.x + (s1Pos.x - s2Pos.x) * (radiiDist - dist)/ (2*dist+.0000001), // + .0000001 so we don't get divide by 00 errors
						  s1Pos.y + (s1Pos.y - s2Pos.y) * (radiiDist - dist)/ (2*dist+.0000001),
						  s1Pos.z + (s1Pos.z - s2Pos.z) * (radiiDist - dist)/ (2*dist+.0000001));
                   glm::vec3 s2NewPos = glm::vec3(s2Pos.x + (s2Pos.x - s1Pos.x) * (radiiDist - dist)/ (2*dist+.0000001),
						  s2Pos.y + (s2Pos.y - s1Pos.y) * (radiiDist - dist)/ (2*dist+.0000001),
						  s2Pos.z + (s2Pos.z - s1Pos.z) * (radiiDist - dist)/ (2*dist+.0000001));
                   s1.setPos(s1NewPos);
                   s2.setPos(s2NewPos);
		   almostDone = false;
                }
            }
        }
	if(almostDone){
		notDone = false;
	}
        almostDone = true;
    }

}

void updateScene(vector <Sphere *> balls) {
	updateBallPositions(balls);
	resolveCollisions(balls);


}


void distanceCheck(vector <Sphere *> balls){
	updateBallPositions(balls);

  /* 
  Naive algorithm via iterative refinement that loops until no
  collisions found.
  */
  for (int i = 0; i < balls.size(); i++){
    for (int j = 0; j < balls.size(); j++){
      Sphere s1 = *balls.at(i);
      Sphere s2 = *balls.at(j);

      if(s1 == s2){
        continue;
      }
      else{
        glm::vec3 pos1 = s1.getPos();
        glm::vec3 pos2 = s2.getPos();

        double rad1 = s1.getRadius();
        double rad2= s2.getRadius();

        double dist = glm::distance(pos1, pos2);

        if (dist >= (rad1 + rad2)){
          //handle_collision_physics(s1, s2);
          
          i = 0;
          j = 0;
        }
      }
    }
  }
}
