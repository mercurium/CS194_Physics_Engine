#include "Util.h"
#include <stdio.h>
#include <string>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

void printv(glm::vec3& v){
   printf("<%.3f %.3f %.3f>",v[0],v[1],v[2]); 
}

void printmat(glm::mat4& m){
    std::string s("%.2f\t"); 
    std::string format = s+s+s+s+"\n"+s+s+s+s+"\n"+s+s+s+s+"\n"+s+s+s+s+"\n";
    char* cstr = new char[format.length()+1];
    std::strcpy(cstr, format.c_str());
   printf( cstr, m[0][0],m[0][1],m[0][2],m[0][3],
                  m[1][0],m[1][1],m[1][2],m[1][3],
                  m[2][0],m[2][1],m[2][2],m[2][3],
                  m[3][0],m[3][1],m[3][2],m[3][3]);
}

double timestamp()
{
  struct timeval tv;
  gettimeofday (&tv, 0);
  return tv.tv_sec + 1e-6*tv.tv_usec;
}
