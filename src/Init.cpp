#include "Init.h"
#include "variables.h"

using namespace std;

namespace Init{
  bool readDoubles(stringstream &s, const int numvals, double * valuesDouble) {
    for (int i = 0 ; i < numvals ; i++) {
      s >> valuesDouble[i] ; 
      if (s.fail()) {
        cout << "Failed reading value " << i << " will skip\n" ; 
        return false ;
      }
    }
    return true ; 
  }

  bool readInt(stringstream &s, const int numvals, int * valuesInt) {
    for (int i = 0 ; i < numvals ; i++) {
      s >> valuesInt[i] ; 
      if (s.fail()) {
        cout << "Failed reading value " << i << " will skip\n" ; 
        return false ;
      }
    }
    return true ; 
  }

  bool readBool(stringstream &s, const int numvals, bool * valuesBool) {
    for (int i = 0 ; i < numvals ; i++) {
      string boolean;
      s >> boolean; 

      if(boolean.compare("true") != 0) valuesBool[i] = true;
      else if(boolean.compare("false") != 0) valuesBool[i] = false;
      else cout << "Unknown parameter. Neither true/false given\n";
      if (s.fail()) {
        cout << "Failed reading value " << i << " will skip\n" ; 
        return false ;
      }
    }
    return true ; 
  }

  void initialize(const char * filename) {
    string str, cmd; 
    ifstream in;
    in.open(filename); 
    if (in.is_open()) {
      getline (in, str) ; 
      while (in) {
        if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
          // Ruled out comment and blank lines 

          stringstream s(str) ;
          s >> cmd ; 
          int i ; 
          double valuesDouble[10] ;
          int valuesInt[10];
          bool valuesBool[10];
          
          bool validinput ; // validity of input 

          if (cmd == "ball") { 
            validinput = readDoubles(s, 6, valuesDouble);
            if(validinput){
              Sphere *s = new Sphere(glm::vec3(valuesDouble[0], valuesDouble[1], valuesDouble[2]), glm::vec3(valuesDouble[3], valuesDouble[4], valuesDouble[5]));
              (balls).push_back(s);
            }
          } else if(cmd == "light"){
            validinput = readDoubles(s, 6, valuesDouble);
            if(validinput){
              //create light object and add to vector
            }
          } else if(cmd == "distcon"){
            //config text file must parse all balls first!
            validinput = readDoubles(s, 3, valuesDouble);
            if(validinput){
              DistConstr *c = new DistConstr(balls.at(valuesDouble[0]), balls.at(valuesDouble[1]), valuesDouble[2]);
              constraints.push_back(c);
            }
          } else if(cmd == "numballs"){
            validinput = readInt(s, 1, valuesInt);
            if(validinput) numballs = valuesInt[0];
          } else if(cmd == "numlights"){
            validinput = readInt(s, 1, valuesInt);
            if(validinput) numlights = valuesInt[0];
          } else if(cmd == "sensitivity"){
            validinput = readDoubles(s, 1, valuesDouble);
            if(validinput) sensitivity = valuesDouble[0];
          } else if(cmd == "2d"){
            validinput = readBool(s, 1, valuesBool);
            if(validinput) is2D = valuesBool[0];
          } else if(cmd == "shading"){
            validinput = readBool(s, 1, valuesBool);
            if(validinput) shading = valuesBool[0];
          } else if(cmd == "accel"){
            validinput = readDoubles(s, 3, valuesDouble);
            if(validinput){
              for(int i = 0; i < 3; i++) accel[i] = valuesDouble[i];
            }
          } else if(cmd == "camera"){
            validinput = readDoubles(s, 9, valuesDouble);
            if(validinput){
              for(int i = 0; i < 9; i++) camera[i] = valuesDouble[i];
            }
          } else if(cmd == "maxbounds"){
            validinput = readDoubles(s, 3, valuesDouble);
            if(validinput){
              for(int i = 0; i < 3; i++) maxbounds[i] = valuesDouble[i];
            }
          }
        }
        getline (in, str) ; 
      }
    }
    else {
      cerr << "Unable to Open Input Data File " << filename << "\n" ; 
      throw 2 ; 
    } 
  }
}