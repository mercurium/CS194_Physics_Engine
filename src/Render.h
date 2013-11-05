#pragma once
#include <GL/glut.h>
#include <glm/glm.hpp>
#include "Scene.h"
#include "Sphere.h"
#include "Transform.h"

/**
 * Class to manage drawing a Scene. 
 * 
 */
class Render {
    public:
        Render ();
        virtual ~Render ();
        void draw(Scene& scene);
        void drawtest();
        void rotateCamUD(double deg);
        void rotateCamLR(double deg);
        void rotateCamRoll(double deg);
        void translCam(glm::vec3& dist);
        glm::mat4 getPerspective(float fovy);

    private:
        void draw(Sphere& sph);
        glm::vec3 camCenter;
        glm::vec3 camView;
        glm::vec3 camUp;
        double zN;
        double zF;
        double fov;

};
