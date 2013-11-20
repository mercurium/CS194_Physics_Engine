#include "SceneOpt.h"
#include <stdio.h>
#define flr(x) (float)( ((int)(x/HASHGRID_SIZE))*HASHGRID_SIZE)
#define hashfun(p) (int)(p.x*1337+p.y*21337+p.z*57)

float HASHGRID_SIZE = 3;

std::size_t vec3Hash::operator()(const glm::vec3 p) const{
    return hashfun(p);
}

std::size_t vec3Equal::operator()(const glm::vec3 p1, const glm::vec3 p2) const{
    return (p1.x==p2.x) && (p1.y==p2.y) && (p1.z==p2.z);
}

glm::vec3 getBucket(glm::vec3 p1){
    return glm::vec3(flr(p1.x), flr(p1.y), flr(p1.z));
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
        //printf("RoundPos: %.2f,%.2f,%.2f\n",roundedPos[0],roundedPos[1],roundedPos[2]);
        Spheremap::iterator it = map->find(roundedPos);
        //printf("It: %d\n",it);
        //Spherelist* bkt = ((*map)[roundedPos]);
        Spherelist * bkt;
        if( it == (map->end())){ //if roundedPos not in map
            //printf("Adding new bucket: %.2f,%.2f,%.2f\n",roundedPos[0],roundedPos[1],roundedPos[2]);
            bkt = new Spherelist;
            //map->insert( map->begin(), std::pair<glm::vec3, Spherelist*>(roundedPos,bkt));
            ((*map)[roundedPos]) = bkt;
        }else{
            //printf("Bucket exists!\n");
            bkt = (*map)[roundedPos];
        }
        bkt->push_back(sph);
}

bool SceneOpt::contains(glm::vec3 pos){
        glm::vec3 roundedPos = getBucket(pos);
        Spheremap::iterator it = map->find(roundedPos);
        if( it == (map->end())){ //if roundedPos not in map
            return false;
        }
        return true;
}

void SceneOpt::addIntersects(std::vector<Intersection *> &intersects, Sphere *sph, glm::vec3 checkPos){

    glm::vec3 selfpos = sph->getPos();
    if( !contains(checkPos)){
        return;
    }  
    glm::vec3 roundedPos = getBucket(checkPos);
    Spherelist * bkt = (*map)[roundedPos];

    printf("\t\tTesting intersects for (%.2f,%.2f,%.2f)\n",selfpos[0],selfpos[1],selfpos[2]); 
    printf("\t\tChecking at (%.2f,%.2f,%.2f)\n",checkPos[0],checkPos[1],checkPos[2]); 
    for( Spherelist::iterator it = bkt->begin(); it!=bkt->end(); ++it){
        Sphere * other = *it;
        //do not check against self
        if( other == sph){ continue;}
        glm::vec3 otherpos = other->getPos();
        //do not insert duplicate intersections
        if( hashfun(selfpos)< hashfun(otherpos)){continue;}
        

        printf("\t\t\tTest: (%.2f,%.2f,%.2f) X (%.2f,%.2f,%.2f)\n", selfpos[0],selfpos[1],selfpos[2],otherpos[0],otherpos[1],otherpos[2]);

        double dist = glm::distance(selfpos, otherpos);
        double radiiDist = sph->getRadius() + other->getRadius();
        if (dist < radiiDist-.001){ // .001 to avoid rounding error
            printf("\t\t\t ## New intersect!\n");
            intersects.push_back(new Intersection( sph, other));
        }else{
            printf("\t\t\t @@ No intersect. dist=%.2f, radii=%.2f\n",dist, radiiDist);
        }
    }
}

void SceneOpt::test(){
    printf("hi\n");
}

std::vector<Intersection *> SceneOpt::getCollisions(){
    //TODO: rehash balls

    std::vector<Intersection *> intersects;
    printf("Getting spheres\n");
    for( Spheremap::iterator iter = map->begin(); iter!=map->end();++iter){
        glm::vec3 key = iter->first;
        printf("At hash: %.2f,%.2f,%.2f\n",key[0],key[1],key[2]);
        Spherelist* vals = iter->second;
        for(Spherelist::iterator it = vals->begin(); it!=vals->end(); ++it){
            Sphere * sph = *it;
            glm::vec3 pos = sph->getPos();
            printf("\tSph: %.2f,%.2f,%.2f\n", pos[0],pos[1],pos[2]);
            //check for intersections on 27 surrounding cells.
            for(int i=0; i<3; i++){
                for(int j=0; j<3; j++){
                    for(int k=0; k<3; k++){
                        glm::vec3 checkPos( key[0]+HASHGRID_SIZE*(i-1), 
                                            key[1]+HASHGRID_SIZE*(j-1),
                                            key[2]+HASHGRID_SIZE*(k-1));
                        addIntersects(intersects, sph, checkPos);
                    }
                }
            }
        }
    }
    for(std::vector<Intersection *>::iterator it = intersects.begin(); it!= intersects.end(); ++it){
        Intersection i = **it;
        Sphere* s1 = i.getS1(), *s2 = i.getS2();
        glm::vec3 s1p = s1->getPos();
        glm::vec3 s2p = s2->getPos();
        printf("Int: (%.2f,%.2f,%.2f) X (%.2f,%.2f,%.2f)\n", s1p[0],s1p[1],s1p[2],s2p[0],s2p[1],s2p[2]);
    }
    return intersects;
}
