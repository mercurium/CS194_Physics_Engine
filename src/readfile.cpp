
// Basic includes to get this file to work.  
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <GL/glut.h>

using namespace std ;
#include "readfile.h"


// The function below applies the appropriate transform to a 4-vector

// Function to read the input data values
// Use is optional, but should be very helpful in parsing.  
bool readvals(stringstream &s, const int numvals, GLfloat * values) {
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

  int numB = 0, numused = 0;
  int count = 0;
  if (in.is_open()) {


    getline (in, str) ; 
    while (in) {
      if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
        // Ruled out comment and blank lines 

        stringstream s(str) ;
        s >> cmd ; 
        int i ; 
        GLfloat values[10] ; // position and color for light, colors for others
                             // Up to 10 params for cameras.  
        bool validinput ; // validity of input 


		if (cmd == "numballs"){
			validinput = readvals(s, 1, values);
    		if (validinput) {
				numballs = (int)values[0];
   			 }
			
		}
		else if (cmd == "numlights"){
			validinput = readvals(s, 1, values);
    		if (validinput) {
				numlights = (int)values[0];
   			 }
		}
		else if (cmd == "sensitivity"){
			validinput = readvals(s, 1, values);
    		if (validinput) {
				sensitivity = values[0];
   			 }
		}
		else if (cmd == "windowsize"){
			validinput = readvals(s, 2, values);
    		if (validinput) {
	  			width = (int)values[0];
	  			height = (int)values[1];
   			 }
		}
		else if (cmd == "accel"){
			validinput = readvals(s, 3, values);
    		if (validinput) {
				for(i = 0; i < 3; i++){ accel[i] = values[i];}
   			 }
			
		}
        else if (cmd == "camera") {
          validinput = readvals(s,9,values) ;
          if (validinput) {
			for(i = 0; i < 9; i++){
				camera[i] = values[i];
			}
          }
        }
		else if (cmd == "minbounds"){
			validinput = readvals(s, 3, values);
    		if (validinput) {
				for(i =0; i < 3; i++){ minbounds[i] = values[i];}
   			 }
		}

		else if (cmd == "maxbounds"){
			validinput = readvals(s, 3, values);
    		if (validinput) {
				for(i =0; i < 3; i++){ maxbounds[i] = values[i];}
   			 }
		}
		else if (cmd == "2d"){
			validinput = readvals(s, 1, values);
    		if (validinput) {
				is2D = ((int)(values[0]+.3) == 1) ? true : false;
   			 }
			
		}
		else if (cmd == "shading"){
			validinput = readvals(s, 1, values);
    		if (validinput) {
				shading = ((int)(values[0]+.3) == 1) ? true : false;
   			 }
		}


        else if (cmd == "ball") { 
          if (numB == numballs)
            cerr << "Reached Maximum Number of Balls " << numB << " Will ignore further ballss\n" ;
          else {
            validinput = readvals(s, 6, values) ; // Position/color for lts.
            if (validinput) {
			  balls.push_back(new Sphere(values[0],values[1],values[2],is2D));
			  balls.at(numB)->setVelocity(glm::vec3(values[3],values[4],values[5]));
              ++numB ; 
            }
          }
        }
        else if (cmd == "distcon"){
          validinput = readvals(s, 3, values) ; // Position/color for lts.
          if (validinput) {
				constraints.push_back(new DistConstr(balls.at((int)values[0]), balls.at((int)values[1]), values[2]));
            }
          }

        // Process the light, add it to database.
        // Lighting Command
        else if (cmd == "light") { 
          if (numused == numlights) // No more Lights 
            cerr << "Reached Maximum Number of Lights " << numused << " Will ignore further lights\n" ;
          else {
            validinput = readvals(s, 6, values) ; // Position/color for lts.
            if (validinput) {
              for (i = 0 ; i < 3 ; i++){
                lightposn[numused *3+i] = values[i];
                lightcolor[numused*3+i] = values[i+3];
              }
              ++numused ; 
            }
          }
        }
        
        else {
          cerr << "Unknown Command: " << cmd << " Skipping \n" ; 
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
