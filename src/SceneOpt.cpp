#include "SceneOpt.h"
#include <stdio.h>


struct sameBucket{
    bool operator()(const glm::vec3 p1, const glm::vec3 p2) const{
        //glm::vec3 tmp1(((int)(p1.x*1)),((int)(p1.y*1)),((int)(p1.z*1)));
        //glm::vec3 tmp2(((int)(p2.x*1)),((int)(p2.y*1)),((int)(p2.z*1)));
        //return (tmp1.x==tmp2.x) && (tmp1.y==tmp2.y) && (tmp1.z==tmp2.z);
        return (p1.x==p2.x) && (p1.y==p2.y) && (p1.z==p2.z);
    }
};

glm::vec3 getBucket(glm::vec3 p1){
    return glm::vec3((float)((int)(p1.x*1)),(float)((int)(p1.y*1)),(float)((int)(p1.z*1)));
}

SceneOpt::SceneOpt(){
    map = new Spheremap;
}

SceneOpt::SceneOpt(std::vector<Sphere *> balls){
    //std::map<glm::vec3 , std::vector<Sphere *>*, sameBucket>*  map;
    map = new Spheremap;
    for(Spherelist::iterator it = balls.begin(); it!=balls.end(); ++it){
        Sphere * sph = *it;
        addSphere(sph);
        //glm::vec3 pos = sph->getPos();
        //printf("Sph: %.2f,%.2f,%.2f\n", pos[0],pos[1],pos[2]);
    }
}

SceneOpt::~SceneOpt(){
    //delete all buckets in map
    delete map;
}

void SceneOpt::addSphere(Sphere * sph){
        glm::vec3 roundedPos = getBucket(sph->getPos());
        printf("RoundPos: %.2f,%.2f,%.2f\n",roundedPos[0],roundedPos[1],roundedPos[2]);
        Spheremap::iterator it = map->find(roundedPos);
        //printf("It: %d\n",it);
        //Spherelist* bkt = ((*map)[roundedPos]);
        Spherelist * bkt;
        if( it == (map->end())){
            printf("Adding new bucket: %.2f,%.2f,%.2f\n",roundedPos[0],roundedPos[1],roundedPos[2]);
            bkt = new Spherelist;
            //map->insert( map->begin(), std::pair<glm::vec3, Spherelist*>(roundedPos,bkt));
            ((*map)[roundedPos]) = bkt;
        }else{
            printf("Bucket exists!\n");
            bkt = (*map)[roundedPos];
        }
        bkt->push_back(sph);
}

void SceneOpt::test(){
    printf("hi\n");
}

std::vector<Intersection *> SceneOpt::getCollisions(){
    std::vector<Intersection *> intersects;
    //TODO: Implement hashtable-based collision detection
    printf("Getting spheres\n");
    for( Spheremap::iterator iter = map->begin(); iter!=map->end();++iter){
        glm::vec3 key = iter->first;
        printf("At pos: %.2f,%.2f,%.2f\n",key[0],key[1],key[2]);
        /*
        Spherelist* vals = iter->second;
        for(Spherelist::iterator it = vals->begin(); it!=vals->end(); ++it){
            Sphere * sph = *it;
            glm::vec3 pos = sph->getPos();
            printf("Sph: %.2f,%.2f,%.2f\n", pos[0],pos[1],pos[2]);
        }
        */
    }

    return intersects;
}
