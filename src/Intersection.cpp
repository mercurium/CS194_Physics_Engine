#include "Intersection.h"

Intersection::Intersection(Sphere *b1, Sphere *b2, double distance, double radiiDistance){
	s1 = b1;
	s2 = b2;
	dist = distance;
	radiiDist = radiiDistance;
}

Intersection::~Intersection (){
    //Deconstructor
}

Sphere * Intersection::getS1(){
	return s1;
}

Sphere * Intersection::getS2(){
	return s2;
}

double Intersection::getDist(){
	return dist;
}


double Intersection::getRadiiDist(){
	return radiiDist;
}
