#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

#include <variables.h>

#include "Sphere.h"
#include "DistConstr.h"

#include <glm/glm.hpp>

namespace Init{
	public:
		void initialize(const char * filename);

	private:
		bool readDoubles(stringstream &s, const int numvals, double * valuesDouble);
		bool readInt(stringstream &s, const int numvals, int * valuesInt);
		 bool readBool(stringstream &s, const int numvals, bool * valuesBool)
		void readfile(const char * filename);
}