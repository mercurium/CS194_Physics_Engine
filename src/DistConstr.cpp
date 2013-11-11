#include "DistConstr.h"
//Constructor
DistConstr::DistConstr(Sphere* a, Sphere* b, double d){ 
    s1 = a;
    s2 = b;

    distance = d;
}

//Deconstructor
DistConstr::~DistConstr(){ 

}

Sphere* DistConstr::getBall(int i){
	if(i == 1){
		return s1;
	} else if(i == 2){
		return s2;
	} else{
		return NULL;
	}
}

double DistConstr::getDist(){
	return distance;
}

bool DistConstr::contains(Sphere* a){
	return (*s1 == *a) || (*s2 == *a);
}

bool DistConstr::contains(Sphere* a, Sphere* b){
	return (*s1 == *a && *s2 == *b) || (*s2 == *a && *s1 == *b);
}