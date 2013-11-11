#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>	
#include <vector>

#include <glm/glm.hpp>

#include "Sphere.h"
#include "DistConstr.h"

using namespace std;

namespace Init{
	void initialize(const char * filename);

	bool readDoubles(stringstream &s, const int numvals, double * valuesDouble);
	bool readInt(stringstream &s, const int numvals, int * valuesInt);
	bool readBool(stringstream &s, const int numvals, bool * valuesBool);
}