#include "Physics.h"
#include <stdio.h>
#include "mmintrin.h"
#include <omp.h>

int LIMIT = 100;
int GRID_SIZE = 10;

namespace Physics{

void UpdateBallPositions(Sphere* balls, int num_balls, double t){
	/*  Update each ball to the new location  */
	#pragma omp parallel for
	for (int i = 0; i < num_balls; i++){
		Sphere &ball = balls[i];
		glm::simdVec4 oldPos = ball.getPos();
		ball.setOldPos(oldPos);
		glm::simdVec4 oldVl = ball.getVelocity();
		
		oldVl += t*accel;

		if(glm::dot(oldVl,oldVl) < t){
			oldVl = glm::detail::fvec4SIMD(0, 0, 0, 0);
		} else{
			glm::simdVec4 newPos = oldPos + t*oldVl;
			ball.setPos(newPos);
		}

		ball.setVelocity(oldVl);
	}
}
void UpdateBallBoundaries(Sphere* balls, int num_balls){
	const __m128 two_scalar = _mm_set1_ps(2);
	const __m128 one_scalar = _mm_set1_ps(1);
	glm::simdVec4 y_min_vel_damp = glm::simdVec4(0.8f, 0.5f, 0.8f, 0.0f);
	
	/*  Update each ball to the new location  */
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

void resolveCollisions(Intersection** intersections, int num_collisions){
	double dist, radiiDist;

	#pragma omp parallel for
	for(int k = 0; k < num_collisions; k++)
	{
		Intersection* iptr = intersections[k];
		Intersection i = *iptr;

		//intersections.pop_back();
		Sphere* s1 = i.getS1(), *s2 = i.getS2();
		glm::simdVec4 s1Pos = s1->getPos();
		glm::simdVec4 s2Pos = s2->getPos();
		
		dist = glm::distance(s1Pos,s2Pos);
		radiiDist = s1->getRadius() + s2->getRadius();
		double distDiff = (radiiDist - dist)/(2*dist);

		glm::simdVec4 s1NewPos = s1Pos + (s1Pos - s2Pos) * distDiff;
		glm::simdVec4 s2NewPos = s2Pos + (s2Pos - s1Pos) * distDiff;
		
		s1->setPos(s1NewPos);
		s2->setPos(s2NewPos);

		glm::simdVec4 s1Vel = s1->getVelocity();
		glm::simdVec4 s2Vel = s2->getVelocity();

		s1Vel *= glm::detail::fvec4SIMD(0.0, 0.0, 0.9, 0.0); //s1Vel.y *= .9;
		s2Vel *= glm::detail::fvec4SIMD(0.0, 0.0, 0.9, 0.0); //s2Vel.y *= .9;

		s1->setVelocity(s2Vel);
		s2->setVelocity(s1Vel);
		
		delete iptr;
	}
}

void handleDistanceConstr(DistConstr* constraints, int constr_size){
	#pragma omp parallel for
	for (int i = 0; i < constr_size; i++)
	{
		DistConstr constr = constraints[i];

		Sphere *s1 = (constr).getBall(1);
		Sphere *s2 = (constr).getBall(2);

		double actual_dist = glm::distance((*s1).getPos(), (*s2).getPos());
		double constr_dist = (constr).getDist();

		double diff = constr_dist - actual_dist;

		glm::simdVec4 s1Pos = (*s1).getPos();
		glm::simdVec4 s2Pos = (*s2).getPos();

		glm::simdVec4 s1NewPos = s1Pos + (s1Pos - s2Pos) * diff/(2*actual_dist);
		glm::simdVec4 s2NewPos = s2Pos + (s2Pos - s1Pos) * (diff)/(2*actual_dist);
		
		(*s1).setPos(s1NewPos);
		(*s2).setPos(s2NewPos);
	}
}

void setLimit(int n){
	LIMIT = n;
}

}
