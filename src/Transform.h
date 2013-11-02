#pragma once
#include <glm/glm.hpp>

/**
 * Push a glm matrix onto the OpenGL matrix stack.
 * (To deal with row/column major inconsistencies between OpenGL/glm)
 */
void push_glm_matrix(glm::mat4 mat);

glm::vec3 applyTransform(glm::vec3& v, glm::mat4& m);
glm::mat4 rotate(glm::vec3& v, double deg);
glm::mat4 translate(glm::vec3& v);

/*
 * Returns the Model+View+Projection matrix
 */
glm::mat4 getCamMatrix(glm::vec3& camCenter, glm::vec3& camUp, glm::vec3& camView,
                       double zNear, double zFar, double aspect, double fov);
