#include <DistConstr.h>
#include <Sphere.h>
// This is the basic include file for the global variables in the program.  
// Since all files need access to it, we define EXTERN as either blank or 
// extern, depending on if included in the main program or not.  

#ifdef MAINPROGRAM 
#define EXTERN 
#else 
#define EXTERN extern 
#endif 

EXTERN int numballs;
EXTERN int numlights;

EXTERN double sensitivity;

EXTERN bool is2D;
EXTERN bool shading;

EXTERN double[3] accel;
EXTERN double[9] camera;
EXTERN double[3] maxbounds; 

EXTERN std::vector<Sphere*> balls;
EXTERN std::vector<DistConstr*> constraints;

/*
EXTERN int numobjects ; 
EXTERN struct object {
  shape type ; 
  GLfloat size ;
  GLfloat ambient[4] ; 
  GLfloat diffuse[4] ; 
  GLfloat specular[4] ;
  GLfloat emission[4] ; 
  GLfloat shininess ;
  mat4 transform ; 
} objects[maxobjects] ;
*/