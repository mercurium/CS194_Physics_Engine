
#include "Scene.h"
#include "Intersections.h"

//Constructor
Scene::Scene(){ 
    
}
//Deconstructor
Scene::~Scene(){ 


}

std::vector<Intersection> Scene::getIntersections(Sphere &obj){
    //Geometry intersection routine
}

void updateBallPositions(){
    /*  Update each ball to the new location  */
    for (int i = 0; i < balls.size(); i++){
       glm::vec3 oldPos = balls.at(i).getPos();
       glm::vec3 oldVl = balls.at(i).getVelocity;
       glm::vec3 newPos = glm::vec3(oldPos.x + oldVl.x, oldPos.y + oldVl.y, oldPos.z + oldVl.z);
       balls.at(i).setPos(newPos);
    }

}

void resolveCollisions(){


}


void updateScene() {
    updateBallPositions();
    bool notDone = true;
    while (notDone){
        for(int i = 1; i < balls.size(); i++){ //First computer all the intersections that happen
            for(int j = 0; j < i; j++){
                Sphere *s1 = balls.at(i);
                Sphere *s2 = balls.at(j);
                double dist = glm::distance(s1.getPos(), s2.getPos());
                double radiiDist = s1.getRadii + s2.getRadii;
                if (dist < radiiDist){
                   glm::vec3 s1NewPos =  
                    
                    
                    
                    
                }
            }
        }
             
    }



}


void distanceCheck(){
	updateBallPositions();
	bool done = false;

	while(!done){
		for (int i = 0; i < balls.size(); i++){
			for (int j = 0; j < balls.size(); j++){
				Sphere s1* = balls.at(i);
				Sphere s2* = balls.at(j);

				if(s1 == s2){
					continue;
				}
				else{
					glm::vec3 pos1 = s1.getPos();
					glm::vec3 pos2 = s2.getPos();

					dist = (pos1 - pos2).mag();

					if (dist >= 1)
					{
						handle_collision_physics(s1, s2);
						
						i = 0;
						j = 0;
					}
				}
			}
		}
	}
}