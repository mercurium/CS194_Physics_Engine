#pragma once
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/**
 * Push a glm matrix onto the OpenGL matrix stack.
 * (To deal with row/column major inconsistencies between OpenGL/glm)
 */
void load_glm_matrix(glm::mat4 mat);

glm::vec3 applyTransform(glm::vec3& v, glm::mat4& m);
glm::mat4 rotate(glm::vec3& v, float deg);
glm::mat4 translate(glm::vec3& v);

/*
 * Returns the Model+View+Projection matrix
 */
void loadCamMatrix(glm::vec3& camCenter, glm::vec3& camUp, glm::vec3& camView);
glm::mat4 getCamMatrix(glm::vec3& camCenter, glm::vec3& camUp, glm::vec3& camView);
glm::mat4 lookAt(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up);
