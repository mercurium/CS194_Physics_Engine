#include "Intersection.h"

Intersection::Intersection(Sphere *b1, Sphere *b2){
	s1 = b1;
	s2 = b2;
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


void Intersection::print(){
	Sphere S1 = *s1, S2 = *s2;
	S1.print();
	S2.print();
	printf("The two spheres are %f apart \n", glm::distance(S1.getPos(), S2.getPos()));

}
