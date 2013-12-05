#include "DistConstr.h"
#include "Sphere.h"

#include <glm/gtx/simd_vec4.hpp>

#include "mmintrin.h"

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

EXTERN glm::simdVec4 accel;
EXTERN double camera[9];
EXTERN __m128 maxbounds;
EXTERN __m128 minbounds;
EXTERN double minbound_y;
EXTERN double maxbounds_array[3];
EXTERN double minbounds_array[3];

EXTERN double lightposn[40];
EXTERN double lightcolor[40];

EXTERN Sphere* balls;
EXTERN DistConstr* constraints;
