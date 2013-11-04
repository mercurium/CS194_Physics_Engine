
#include "Scene.h"
using namespace std;
//Constructor
Scene::Scene(){ 
    balls = new std::vector<Sphere *>;
}
//Deconstructor
Scene::~Scene(){ 


}

std::vector<Intersection> Scene::getIntersections(Sphere &obj){
    //Geometry intersection routine
}

void updateBallPositions(vector<Sphere *> balls){
    /*  Update each ball to the new location  */
    for (int i = 0; i < balls.size(); i++){
       glm::vec3 oldPos = (&balls.at(i)).getPos();
       glm::vec3 oldVl = (&balls.at(i)).getVelocity;
       glm::vec3 newPos = glm::vec3(oldPos.x + oldVl.x, oldPos.y + oldVl.y, oldPos.z + oldVl.z);
       balls.at(i).setPos(newPos);
    }

}


void updateScene(vector <Sphere *> balls) {
    updateBallPositions(balls);
    bool notDone = true, almostDone = true;
    while (notDone){
        for(int i = 1; i < balls.size(); i++){ //First computer all the intersections that happen
            for(int j = 0; j < i; j++){
                Sphere s1 = *balls.at(i);
                Sphere s2 = *balls.at(j);
                double dist = glm::distance(s1.getPos(), s2.getPos());
                double radiiDist = s1.getRadius + s2.getRadius;
                if (dist < radiiDist){
                   glm::vec3 s1Pos = s1.getPos();
                   glm::vec3 s2Pos = s2.getPos();
                   glm::vec3 s1NewPos = glm::vec3(s1Pos.x + (s1Pos.x - s2Pos.x) * (radiiDist - dist)/ (2*dist+.0001), // + .0001 so we don't get divide by 0 errors
						  s1Pos.y + (s1Pos.y - s2Pos.y) * (radiiDist - dist)/ (2*dist+.0001),
						  s1Pos.z + (s1Pos.z - s2Pos.z) * (radiiDist - dist)/ (2*dist+.0001));
                   glm::vec3 s2NewPos = glm::vec3(s2Pos.x + (s2Pos.x - s1Pos.x) * (radiiDist - dist)/ (2*dist+.0001),
						  s2Pos.y + (s2Pos.y - s1Pos.y) * (radiiDist - dist)/ (2*dist+.0001),
						  s2Pos.z + (s2Pos.z - s1Pos.z) * (radiiDist - dist)/ (2*dist+.0001));
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
