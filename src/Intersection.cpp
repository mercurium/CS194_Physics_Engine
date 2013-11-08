#include "Intersection.h"

Intersection::Intersection(Sphere *s1, Sphere *s2, double dist){
	this.s1 = s1;
	this.s2 = s2;
	this.dist = dist;
}

Intersection::Intersection(){
    //Constructor
}
Intersection::~Intersection (){
    //Deconstructor
}
