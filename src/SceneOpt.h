#pragma once
#include "Scene.h"
#include <map>


struct sameBucket;
typedef std::map<glm::vec3 , std::vector<Sphere *>*, sameBucket> Spheremap;
typedef std::vector<Sphere *> Spherelist;


glm::vec3 getBucket(glm::vec3 p1);

class SceneOpt : public Scene {
    public:
        SceneOpt();
        SceneOpt(std::vector<Sphere *> balls);
        ~SceneOpt();
        void test();
        std::vector<Intersection *> getCollisions();
        void addSphere(Sphere * sph);
    private:
        //std::map<glm::vec3 , std::vector<Sphere *>*, sameBucket>*  map;
        Spheremap * map; 
};
