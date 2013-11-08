
#include "Scene.h"


namespace  Scene{

void updateBallPositions(std::vector<Sphere *> balls){
    /*  Update each ball to the new location  */
    for (int i = 0; i < balls.size(); i++){
       Sphere ball = *balls.at(i);
       glm::vec3 oldPos = ball.getPos();
	   ball.setOldPos(oldPos);
       glm::vec3 oldVl = ball.getVelocity();
       glm::vec3 newPos = glm::vec3(oldPos.x + oldVl.x, oldPos.y + oldVl.y, oldPos.z + oldVl.z);
       ball.setPos(newPos);
    }

}

std::vector <Sphere *> makeTestScene(){
	std::vector <Sphere *> balls;
	double x,y,z;
	for (int i = 0; i < 20; i++){
		x = (i*i + 3*i+504)%100 + i/20.;
		y = (2*i*i - i + 1017)%100 + i/20.;
		z = (5*i*i - 13 *i + 100014) % 100 + i/20.;
		balls.push_back(new Sphere(x,y,z));

	}
	return balls;

}

std::vector<Intersection *> getCollisions(std::vector <Sphere *> balls){
	std::vector<Intersection *> intersects;
    for(int i = 1; i < balls.size(); i++){ //First computer all the intersections that happen
        for(int j = 0; j < i; j++){
            Sphere s1 = *balls.at(i);
            Sphere s2 = *balls.at(j);
            double dist = glm::distance(s1.getPos(), s2.getPos());
            double radiiDist = s1.getRadius() + s2.getRadius();
            if (dist < radiiDist){
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
		Intersection i = *intersections.back();
		intersections.pop_back();
		Sphere s1 = *i.getS1(), s2 = *i.getS2();
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
	}
}

void UpdateScene(std::vector <Sphere *> balls) {
	updateBallPositions(balls);

	std::vector <Intersection *> intersections = getCollisions(balls);

	while (intersections.size()  != 0){
		resolveCollisions(intersections);
		intersections = getCollisions(balls);
	}

	for (int i = 0; i < balls.size(); i++){
		glm::vec3 oldPos = (*balls.at(i)).getOldPos();
		glm::vec3 newPos = (*balls.at(i)).getPos();
		glm::vec3 velocity = glm::vec3( newPos.x - oldPos.x, newPos.y- oldPos.y, newPos.z - oldPos.z);
		(*balls.at(i)).setVelocity(velocity);
	}
}

}
