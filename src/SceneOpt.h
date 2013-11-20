#pragma once
#include "Scene.h"
#include <unordered_map>
#include <tuple>


class vec3Hash{
    public:
        std::size_t operator()(const glm::vec3 p) const;
};
class vec3Equal{
    public:
        std::size_t operator()(const glm::vec3 p1, const glm::vec3 p2) const;
};

typedef std::unordered_map<glm::vec3 , std::vector<Sphere *>*, vec3Hash, vec3Equal> Spheremap;
typedef std::vector<Sphere *> Spherelist;
typedef std::tuple<Sphere *, Spherelist *, Spheremap::iterator, Spherelist::iterator> BadSphereTuple;


glm::vec3 getBucket(glm::vec3 p1);

class SceneOpt : public Scene {
    public:
        SceneOpt();
        SceneOpt(std::vector<Sphere *> balls);
        ~SceneOpt();
        void test();
        std::vector<Intersection *> getCollisions();
        void addSphere(Sphere * sph);
        bool contains(glm::vec3 pos);
    private:
        Spheremap * map; 
        void addIntersects(std::vector<Intersection *> &intersects, Sphere *sph, glm::vec3 checkPos);
};
