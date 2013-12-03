#include "DistConstr.h"
#include "Sphere.h"

#include <glm/gtx/simd_vec4.hpp>

#include "pmmintrin.h"

// This is the basic include file for the global variables in the program.  
// Since all files need access to it, we define EXTERN as either blank or 
// extern, depending on if included in the main program or not.  
#ifdef MAINPROGRAM 
#define EXTERN 
#else 
#define EXTERN extern 
#endif 

EXTERN int numballs;
EXTERN int numcons;
EXTERN int numlights;
EXTERN int height;
EXTERN int width;

EXTERN double sensitivity;

EXTERN bool is2D;
EXTERN bool shading;

EXTERN glm::detail::fvec4SIMD accel;
EXTERN double camera[9];
EXTERN __m128 maxbounds;
EXTERN __m128 minbounds;
EXTERN double minbound_y;
//EXTERN double maxbounds[3]; 
//EXTERN double minbounds[3]; 

EXTERN double lightposn[40];
EXTERN double lightcolor[40];


EXTERN Sphere* balls;
EXTERN DistConstr* constraints;

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
