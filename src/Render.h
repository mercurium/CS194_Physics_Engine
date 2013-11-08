#pragma once
#include <GL/glut.h>
#include <glm/glm.hpp>
#include "Scene.h"
#include "Sphere.h"
#include "Transform.h"
#include "shaders.h"

void pr(glm::vec3& v);
/**
 * Class to manage drawing a Scene. 
 * 
 */
class Render {
    public:
        Render ();
        virtual ~Render ();
        void draw(std::vector<Sphere*> spheres);
        void drawtest();
        void rotateCamUD(double deg);
        void rotateCamLR(double deg);
        void rotateCamRoll(double deg);
        void translCam(glm::vec3& dist);
        void translCamFB(double dist);
        void translCamUD(double dist);
        void translCamLR(double dist);
        glm::mat4 getPerspective(float fovy);

        Shader * shader;

    private:
        void draw(Sphere& sph);
        glm::vec3 camCenter;
        glm::vec3 camView;
        glm::vec3 camUp;
        double zN;
        double zF;
        double fov;
};
