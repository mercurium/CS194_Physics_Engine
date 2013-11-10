#include "Init.h"

namespace Init{
  void initialize(std::vector<Sphere*> *balls, std::vector<Lights*> *lights, std::vector<DistConstr*> *constraints; std::map<string, int> dict, const char * filename){
    balls = balls;
    lights = lights;
    constraints = constraints;
    dict = dict;

    readfile(filename);
  }

  bool readvals(stringstream &s, const int numvals, double * values) {
    for (int i = 0 ; i < numvals ; i++) {
      s >> values[i] ; 
      if (s.fail()) {
        cout << "Failed reading value " << i << " will skip\n" ; 
        return false ;
      }
    }
    return true ; 
  }

  void readfile(const char * filename) {
    string str, cmd ; 
    ifstream in ;
    in.open(filename) ; 
    if (in.is_open()) {
      getline (in, str) ; 
      while (in) {
        if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
          // Ruled out comment and blank lines 

          stringstream s(str) ;
          s >> cmd ; 
          int i ; 
          double values[10] ; // position and color for light, colors for others
                               // Up to 10 params for cameras.  
          bool validinput ; // validity of input 

          // Process the light, add it to database.
          // Lighting Command
          if (cmd == "ball") { 
            validinput = readvals(s, 6, values);
            if(validinput){
              (*balls).push_back(new Sphere(glm::vec3(values[0], values[1], values[2]), glm::vec3(values[3], values[4], values[5])));
            }
          } else if(cmd == "light"){
            validinput = readvals(s, 6, values);
            if(validinput){
              //create light object and add to vector
            }
          } else if(cmd == "distcon"){
            validinput = readvals(s, 3, values);
            if(validinput){
              (*constraints).push_back(new DistConstr(a, b, values[2]))
            }
          } else{
            validinput = readvals(s, 1, values);
            if(validinput){
              (*constraints).push_back(new DistConstr(a, b, values[2]))
            }
          }

          // I've left the code for loading objects in the skeleton, so 
          // you can get a sense of how this works.  
          else if (cmd == "sphere" || cmd == "cube" || cmd == "teapot") {
            if (numobjects == maxobjects) // No more objects 
              cerr << "Reached Maximum Number of Objects " << numobjects << " Will ignore further objects\n" ; 
            else {
              validinput = readvals(s, 1, values) ; 
              if (validinput) {
                object * obj = &(objects[numobjects]) ; 
                obj -> size = values[0] ; 
                for (i = 0 ; i < 4 ; i++) {
                  (obj -> ambient)[i] = ambient[i] ; 
                  (obj -> diffuse)[i] = diffuse[i] ; 
                  (obj -> specular)[i] = specular[i] ; 
                  (obj -> emission)[i] = emission[i] ;
                }
                obj -> shininess = shininess ; 
                obj -> transform = transfstack.top() ; 
                if (cmd == "sphere") obj -> type = sphere ; 
                else if (cmd == "cube") obj -> type = cube ; 
                else if (cmd == "teapot") obj -> type = teapot ; 
              }
              ++numobjects ; 
            }
          }
        }
        getline (in, str) ; 
      }

    // Set up initial position for eye, up and amount
    // As well as booleans 

          eye = eyeinit ; 
    up = upinit ; 
    amount = 5;
          sx = sy = 1.0 ; // scales in x and y 
          tx = ty = 0.0 ; // translation in x and y  
    useGlu = false; // don't use the glu perspective/lookat fns

    glEnable(GL_DEPTH_TEST);

    }
    else {
      cerr << "Unable to Open Input Data File " << filename << "\n" ; 
      throw 2 ; 
    }
    
  }

}