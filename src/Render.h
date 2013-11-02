#pragma once
#include <GL/glut.h>
#include <glm/glm.hpp>
#include "Scene.h"
#include "Sphere.h"

class Render {
    public:
        Render ();
        virtual ~Render ();
        void draw(Scene& scene);
        void rotateCamUD(double deg);
        void rotateCamLR(double deg);
        void rotateCamRoll(double deg);
        void translCam(glm::vec3& dist);

    private:
        void draw(Sphere& sph);
        glm::vec3 camCenter;
        glm::vec3 camView;
        glm::vec3 camUp;

};