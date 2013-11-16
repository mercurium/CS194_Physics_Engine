#pragma once
#include "Scene.h"
#include <map>

class SceneOpt : public Scene {
    public:
        SceneOpt();
        ~SceneOpt();
        std::vector<Intersection *> getCollisions();

};
