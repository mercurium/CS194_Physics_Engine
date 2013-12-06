#include "Physics.h"
#include <stdio.h>
#include <omp.h>

int LIMIT = 100;
int GRID_SIZE = 10;

namespace Physics{

void UpdateBallPositions(Sphere* balls, int num_balls, double t){
	/*  Update each ball to the new location  */
    #pragma omp parallel for
	for (int i = 0; i < num_balls; i++){
		Sphere &ball = balls[i];
        glm::vec3 oldPos = ball.getPos();
		ball.setOldPos(oldPos);
        glm::vec3 oldVl = ball.getVelocity();
		
		oldVl.x += t*accel[0];
        oldVl.y += t*accel[1];
        oldVl.z += t*accel[2];

		if(glm::dot(oldVl,oldVl) < t){
			oldVl = glm::vec3(0, 0, 0);
		} else{
            glm::vec3 newPos = glm::vec3(oldPos.x + oldVl.x*t, oldPos.y + oldVl.y*t, oldPos.z + oldVl.z*t); 
			ball.setPos(newPos);
		}

		ball.setVelocity(oldVl);
	}
}

void UpdateBallBoundaries(Sphere* balls, int num_balls){

	/*  Update each ball to the new location  */
    #pragma omp parallel for
	for (int i = 0; i < num_balls; i++){
		Sphere &ball = balls[i];
		glm::vec3 oldVl = ball.getVelocity();
        glm::vec3 newPos = ball.getPos();
		
		/*Checking for Walls */
		if (newPos.x > maxbounds[0]){
			newPos.x = 2 * maxbounds[0] - newPos.x;
			oldVl.x = -oldVl.x;
		}
		if (newPos.y > maxbounds[1]){
			newPos.y = 2 * maxbounds[1] - newPos.y;
			oldVl.y = -oldVl.y;
		}
		if (newPos.z > maxbounds[2]){
			newPos.z = 2 * maxbounds[2] - newPos.z;
			oldVl.z = -oldVl.z;
		}
		if (newPos.x < minbounds[0]){
			newPos.x = 2 * minbounds[0] - newPos.x;
			oldVl.x = -oldVl.x;
		}
		if (newPos.y < minbounds[1]){
			newPos.y = minbounds[1];
			oldVl.y = -oldVl.y/2.0;
			oldVl.x = oldVl.x * .8;
			oldVl.z = oldVl.z * .8;
		}
		if (newPos.z < minbounds[2]){
			newPos.z = 2 * minbounds[2] - newPos.z;
			oldVl.z = -oldVl.z;
		}

		ball.setPos(newPos);
		ball.setVelocity(oldVl);
	}
}

/*
//SSE'd code actually slows down the program
void UpdateBallBoundaries(Sphere* balls, int num_balls){
        const __m128 two_scalar = _mm_set1_ps(2);
        const __m128 one_scalar = _mm_set1_ps(1);
        glm::simdVec4 y_min_vel_damp = glm::simdVec4(0.8f, 0.5f, 0.8f, 0.0f);
        
        //  Update each ball to the new location 
        #pragma omp parallel for
        for (int i = 0; i < num_balls; i++){
                Sphere &ball = balls[i];

                bool y_true = glm::vec4_cast(ball.getPos()).y < minbound_y;

                __m128 gt_mask = _mm_cmpgt_ps(ball.getPos().Data, maxbounds);
                __m128 lt_mask = _mm_cmplt_ps(ball.getPos().Data, minbounds);
                __m128 lt_gt_mask = _mm_or_ps(lt_mask, gt_mask);

                __m128 gt_offset = _mm_mul_ps(two_scalar, _mm_sub_ps(ball.getPos().Data, maxbounds));
                __m128 lt_offset = _mm_mul_ps(two_scalar, _mm_sub_ps(minbounds, ball.getPos().Data));
                __m128 vel_mul = _mm_sub_ps(_mm_andnot_ps(lt_gt_mask, one_scalar), _mm_and_ps(lt_gt_mask, one_scalar));

                __m128 tmp_pos = _mm_add_ps(ball.getPos().Data, _mm_and_ps(lt_mask, lt_offset));
                //2*(minbounds-ball.getPos().Data) = lt_offset
                //newPos+=oldPos(lt_offset & lt_mask)

                tmp_pos = _mm_sub_ps(tmp_pos, _mm_and_ps(gt_mask, gt_offset));
                //2*(newPos - maxbounds) = gt_offset
                //newPos-=oldPos(gt_offset & gt_mask)

                ball.setPos(glm::detail::fvec4SIMD(tmp_pos));                
                ball.setVelocity(glm::detail::fvec4SIMD(_mm_mul_ps(ball.getVelocity().Data, vel_mul)));

                if(y_true){
                        glm::vec4 vecPos = glm::vec4_cast(ball.getPos());
                        vecPos.y = minbound_y;
                        ball.setPos(glm::detail::fvec4SIMD(vecPos));

                        glm::simdVec4 tmp_vel = ball.getVelocity();
                        tmp_vel *= y_min_vel_damp;
                        ball.setVelocity(tmp_vel);
                }
        }
}
*/


void resolveCollisions(Intersection** intersections, int num_collisions){
	double dist, radiiDist;

    //Data races OK - order that itersections are generated are 
    //undefined, especially once multithreaded.
    #pragma omp parallel for
	for(int k = 0; k < num_collisions; k++)
	//while(num_collisions != 0)
	{
		Intersection* iptr = intersections[k];
		Intersection i = *iptr;

		//intersections.pop_back();
		Sphere* s1 = i.getS1(), *s2 = i.getS2();
        glm::vec3 s1Pos = s1->getPos();
        glm::vec3 s2Pos = s2->getPos();
		
		dist = glm::distance(s1Pos,s2Pos);
		radiiDist = s1->getRadius() + s2->getRadius();
		double distDiff = (radiiDist - dist)/(2*dist);
		double dX = (s1Pos.x - s2Pos.x) * distDiff;
		double dY = (s1Pos.y - s2Pos.y) * distDiff;
		double dZ = (s1Pos.z - s2Pos.z) * distDiff;

        glm::vec3 s1NewPos = glm::vec3(
                s1Pos.x + dX,
                s1Pos.y + dY,
                s1Pos.z + dZ);
		glm::vec3 s2NewPos = glm::vec3(
                s2Pos.x - dX,
                s2Pos.y - dY,
                s2Pos.z - dZ);

		s1->setPos(s1NewPos);
		s2->setPos(s2NewPos);

        glm::vec3 s1Vel = s1->getVelocity();
        glm::vec3 s2Vel = s2->getVelocity();

		s1Vel *= .9;
		s2Vel *= .9;

		s1->setVelocity(s2Vel);
		s2->setVelocity(s1Vel);
		
		delete iptr;
	}

//	delete intersections;
}

void handleDistanceConstr(DistConstr* constraints, int constr_size){

    //Data races OK - further iterations will eventually resolve
    //constraints
    #pragma omp parallel for
	for (int i = 0; i < constr_size; i++)
	{
		DistConstr constr = constraints[i];

		Sphere *s1 = (constr).getBall(1);
		Sphere *s2 = (constr).getBall(2);

		double actual_dist = glm::distance((*s1).getPos(), (*s2).getPos());
		double constr_dist = (constr).getDist();

		double diff = constr_dist - actual_dist;

        glm::vec3 s1Pos = (*s1).getPos();
        glm::vec3 s2Pos = (*s2).getPos();

		double distDiff = diff/(2*actual_dist);
		double dX = (s1Pos.x - s2Pos.x) * distDiff;
		double dY = (s1Pos.y - s2Pos.y) * distDiff;
		double dZ = (s1Pos.z - s2Pos.z) * distDiff;



        glm::vec3 s1NewPos = glm::vec3(
                s1Pos.x + dX,
                s1Pos.y + dY,
                s1Pos.z + dZ);
		glm::vec3 s2NewPos = glm::vec3(
                s2Pos.x - dX,
                s2Pos.y - dY,
                s2Pos.z - dZ);
		

		(*s1).setPos(s1NewPos);
		(*s2).setPos(s2NewPos);
  	}
}

void setLimit(int n){
	LIMIT = n;
}  

}
