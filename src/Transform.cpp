#include "Transform.h"

//Push a glm matrix (accouting for differences in row-vs-column major
void load_glm_matrix(glm::mat4 mat){
    glm::mat4 m = glm::transpose(mat);
    glLoadMatrixf(&m[0][0]);
}

glm::vec3 applyTransform(glm::vec3& v, glm::mat4& m){
    glm::vec4 v4(v[0],v[1],v[2],1);
    glm::vec4 newv = m*v4;
    glm::vec3 homogenized( newv[0]/newv[3],newv[1]/newv[3],newv[2]/newv[3]);
    return homogenized;
}

void loadCamMatrix(glm::vec3& camCenter, glm::vec3& camUp, glm::vec3& camView){

    glm::vec3 viewCenter = camCenter+camView; 
    glm::mat4 mv = glm::lookAt( camCenter, viewCenter, camUp);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glLoadMatrixf(&mv[0][0]);
}

glm::mat4 rotate(glm::vec3& axis, float degrees){
  float costheta = glm::cos((degrees)*.0174532825f);
  float sintheta = glm::sin((degrees)*.0174532825f);
  glm::mat3 matrix1(costheta);

  float x = axis[0];
  float y = axis[1];
  float z = axis[2];
  glm::mat3 matrix2( x*x, x*y, x*z,
               x*y, y*y, y*z,
			   x*z, y*z, z*z);
  matrix2 *= (1-costheta);

  glm::mat3 matrix3(0, -z, y,
			   z, 0, -x,
			  -y,x, 0);
  matrix3 *= sintheta;
  return glm::mat4(matrix1+matrix2+matrix3);
}

glm::mat4 translate(glm::vec3& v){
    glm::mat4 ret(1,0,0, v[0],
                  0,1,0, v[1],
                  0,0,1, v[2],
                  0,0,0, 1);
    return ret;
}

glm::mat4 lookAt(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up) {
    glm::vec3 vecw = glm::normalize(eye-center);
    glm::vec3 vecu = glm::normalize(glm::cross(up, vecw));
    glm::vec3 vecv = glm::cross(vecw, vecu);
    glm::mat4 lookat(vecu[0], vecu[1], vecu[2], -glm::dot(vecu,eye),
              vecv[0], vecv[1], vecv[2], -glm::dot(vecv,eye),
              vecw[0], vecw[1], vecw[2], -glm::dot(vecw,eye),
              0,0,0,1);
	return lookat;
}

glm::mat4 perspective(float fovy, float aspect, float zNear, float zFar)
{
	float theta = fovy/2.0f;
	float d = 1.0f/(glm::tan(theta*.0174532825f));
	float A = -(zFar+zNear)/(zFar-zNear);
	float B = -2.0f*(zFar*zNear)/(zFar-zNear);
	
    glm::mat4 ret( d/aspect, 0, 0, 0,
			  0,d,0,0,
			  0,0,A,B,
			  0,0,-1.0,0);
	return ret;
}

