// Readfile definitions 
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <GL/glut.h>

#include "Sphere.h"
#include "DistConstr.h"
#include "variables.h"

using namespace std;

namespace Read{
	bool readvals(stringstream &s, const int numvals, GLfloat * values);
	void readfile(const char * filename);
}