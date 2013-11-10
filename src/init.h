#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

#include "Sphere.h"
#include "DistConstr.h"


#include <glm/glm.hpp>

class Init{
	std::vector<Sphere*> *balls;
	std::vector<Lights*> *lights
	std::vector<DistConstr*> *constraints;
	std::map<string, int> *dict;

	public:
		void initialize(std::vector<Sphere*> *balls, std::vector<Lights*> *lights, std::map<string, int> dict);

	private:
		bool readvals(stringstream &s, const int numvals, double * values);
		void readfile(const char * filename);
}