#include "Physics.h"
#include <stdio.h>
#include "pmmintrin.h"
#include <omp.h>

int LIMIT = 100;
int GRID_SIZE = 10;

namespace Physics{

void UpdateBallPositions(Sphere* balls, int num_balls, double t){
	/*  Update each ball to the new location  */
	#pragma omp parallel for
	for (int i = 0; i < num_balls; i++){
		Sphere &ball = balls[i];
		simdVec4 oldPos = ball.getPos();
		ball.setOldPos(oldPos);
		simdVec4 oldVl = ball.getVelocity();
		
		oldVl += t*accel;

		if(glm::dot(oldVl,oldVl) < t){
			oldVl = glm::detail::fvec4SIMD(0, 0, 0, 0);
		} else{
			simdVec4 newPos = oldPos + t*oldVl;
			ball.setPos(newPos);
		}

		ball.setVelocity(oldVl);
	}
}

void UpdateBallBoundaries(Sphere* balls, int num_balls){
	const __m128 two_scalar = _mm_set1_ps(2);
	const __m128 one_scalar = _mm_set1_ps(1);
	const __m128 zero_scalar = _mm_set1_ps(0);
	const __m128 y_min_mask = _mm_set_ps(0x0, 0xffffffff, 0x0, 0x0);
	const __m128 y_min_vel_damp = _mm_set_ps(.8, .5, .8, 0);
	
	double bool_lt_mask[4];

	/*  Update each ball to the new location  */
	#pragma omp parallel for
	for (int i = 0; i < num_balls; i++){
		Sphere &ball = balls[i];
		glm::vec4 oldVl = glm::vec4_cast(ball.getVelocity());
		
		//glm::vec4 newPos = glm::vec4_cast(ball.getPos());

		__m128 gt_mask = _mm_cmpgt_ps(ball.getPos().Data, maxbounds);
		__m128 lt_mask = _mm_cmplt_ps(ball.getPos().Data, minbounds);
		__m128 lt_gt_mask = _mm_or_ps(lt_mask, gt_mask);

		_mm_storeu_ps(&bool_lt_mask[0], lt_mask);

		__m128 gt_offset = _mm_mul_ps(two_scalar, _mm_sub_ps(ball.getPos().Data, maxbounds));
		__m128 lt_offset = _mm_mul_ps(two_scalar, _mm_sub_ps(minbounds, ball.getPos().Data));
		__m128 vel_mul = _mm_add_ps(zero_scalar, _mm_sub_ps(_mm_andnot_ps(lt_gt_mask, one_scalar), _mm_and_ps(lt_gt_mask, one_scalar)));

		if(bool_lt_mask[2] < minbound_y){
			__m128 tmp_pos = _mm_add_ps(_mm_sub_ps(ball.getPos.Data, _mm_and_ps(gt_mask, gt_offset)), _mm_and_ps(lt_mask, lt_offset));
			__m128 tmp_pos_y = _mm_set1_ps(minbound_y);

			ball.setPos(glm::detail::fvec4SIMD(_mm_and_ps(_mm_and_ps(y_min_mask, tmp_pos_y), _mm_andnot_ps(y_min_mask, tmp_pos)));
			ball.setVelocity(glm::detail::fvec4SIMD(_mm_mul_ps(y_min_vel_damp, _mm_mul_ps(ball.getVelocity().Data, vel_mul))));
		} else{
			ball.setPos(glm::detail::fvec4SIMD(_mm_add_ps(_mm_sub_ps(ball.getPos.Data, _mm_and_ps(gt_mask, gt_offset)), _mm_and_ps(lt_mask, lt_offset))));
			ball.setVelocity(glm::detail::fvec4SIMD(_mm_mul_ps(ball.getVelocity().Data, vel_mul)));
		}

		//2*(minbounds-ball.getPos().Data) = lt_offset
		//newPos+=oldPos(lt_offset & lt_mask)

		//2*(newPos - maxbounds) = gt_offset
		//newPos-=oldPos(gt_offset & gt_mask)

		/*Checking for Walls */
		// if (newPos.x > maxbounds[0]){
		// 	newPos.x = 2 * maxbounds[0] - newPos.x;
		// 	oldVl.x = -oldVl.x;
		// }
		// if (newPos.y > maxbounds[1]){
		// 	newPos.y = 2 * maxbounds[1] - newPos.y;
		// 	oldVl.y = -oldVl.y;
		// }
		// if (newPos.z > maxbounds[2]){
		// 	newPos.z = 2 * maxbounds[2] - newPos.z;
		// 	oldVl.z = -oldVl.z;
		// }
		// if (newPos.x < minbounds[0]){
		// 	newPos.x = 2 * minbounds[0] - newPos.x;
		// 	oldVl.x = -oldVl.x;
		// }
		// if (newPos.y < minbounds[1]){
		// 	newPos.y = minbounds[1];
		// 	oldVl.y = -oldVl.y/2.0;
		// 	oldVl.x = oldVl.x * .8;
		// 	oldVl.z = oldVl.z * .8;
		// }
		// if (newPos.z < minbounds[2]){
		// 	newPos.z = 2 * minbounds[2] - newPos.z;
		// 	oldVl.z = -oldVl.z;
		// }

		// ball.setPos(glm::detail::fvec4SIMD(newPos));
		// ball.setVelocity(glm::detail::fvec4SIMD(oldVl));
	}

	delete *bool_lt_mask;
}

/*
std::vector<Intersection *> getCollisions(std::vector <Sphere *> &balls){
	std::vector<Intersection *> intersects;
	std::vector <Sphere *> list_of_balls[GRID_SIZE * GRID_SIZE];
	for(int i = 0; i < balls.size(); i++){
		Sphere &s = *balls.at(i);
		int x = s.getPos().x / (100/GRID_SIZE);
		x = std::min(std::max(x,0),GRID_SIZE-1);
		int z = s.getPos().z / (100/GRID_SIZE);
		z = std::min(std::max(z,0),GRID_SIZE-1);
		list_of_balls[x * GRID_SIZE + z].push_back(&s);
	}


	for (int i = 0; i < GRID_SIZE; i++){
		for(int ii = 0; ii <= 1; ii++){
			if (i+ii < 0 || i+ii >= GRID_SIZE){ continue; }


			for (int j = 0; j < GRID_SIZE; j++){
					for (int jj = 0; jj <= 1; jj++){
						if (jj+j < 0 || jj+j >= GRID_SIZE){ continue; }

						int p1 = GRID_SIZE * i + j, p2 = GRID_SIZE * (i+ii) + j + jj;

						for(int b1 = 0; b1 < list_of_balls[p1].size(); b1++){
							for(int b2 = 0; b2 < list_of_balls[p2].size(); b2++){
								if (p1 == p2 && b1 <= b2){ continue; }
								
								double dist = glm::distance((*list_of_balls[p1].at(b1)).getPos(), (*list_of_balls[p2].at(b2)).getPos());
								double radiiDist = (*list_of_balls[p1].at(b1)).getRadius() + (*list_of_balls[p2].at(b2)).getRadius();
								if (dist < radiiDist-.001){ // .001 to avoid rounding error
									intersects.push_back(new Intersection(list_of_balls[p1].at(b1), list_of_balls[p2].at(b2)));
								}
							}
						}
					}
				}		
			}
	}

	This is the non grided version
	for(int i = 1; i < balls.size(); i++){ //First compute all the intersections that happen
		for(int j = 0; j < i; j++){
			double dist = glm::distance((*balls.at(i)).getPos(), (*balls.at(j)).getPos());
			double radiiDist = (*balls.at(i)).getRadius() + (*balls.at(j)).getRadius();
			if (dist < radiiDist-.001){ // .001 to avoid rounding error
				intersects.push_back(new Intersection(balls.at(i),balls.at(j), dist, radiiDist));
			}
		}
	}
	return intersects;
}
*/

void resolveCollisions(Intersection** intersections, int num_collisions){
	double dist, radiiDist;

	#pragma omp parallel for
	for(int k = 0; k < num_collisions; k++)
	//while(num_collisions != 0)
	{
		Intersection* iptr = intersections[k];
		Intersection i = *iptr;

		//intersections.pop_back();
		Sphere* s1 = i.getS1(), *s2 = i.getS2();
		simdVec4 s1Pos = s1->getPos();
		simdVec4 s2Pos = s2->getPos();
		
		dist = glm::distance(s1Pos,s2Pos);
		radiiDist = s1->getRadius() + s2->getRadius();
		double distDiff = (radiiDist - dist)/(2*dist);

		simdVec4 s1NewPos = s1Pos + (s1Pos - s2Pos) * distDiff;
		simdVec4 s2NewPos = s2Pos + (s2Pos - s1Pos) * distDiff;
		
		s1->setPos(s1NewPos);
		s2->setPos(s2NewPos);

		simdVec4 s1Vel = s1->getVelocity();
		simdVec4 s2Vel = s2->getVelocity();

		s1Vel *= glm::detail::fvec4SIMD(0, 0.9, 0, 0); //s1Vel.y *= .9;
		s2Vel *= glm::detail::fvec4SIMD(0, 0.9, 0, 0); //s2Vel.y *= .9;

		s1->setVelocity(s2Vel);
		s2->setVelocity(s1Vel);
		
		delete iptr;
	}

//	delete intersections;
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

		simdVec4 s1Pos = (*s1).getPos();
		simdVec4 s2Pos = (*s2).getPos();

		simdVec4 s1NewPos = s1Pos + (s1Pos - s2Pos) * diff/(2*actual_dist);
		simdVec4 s2NewPos = s2Pos + (s2Pos - s1Pos) * (diff)/(2*actual_dist);
		
		(*s1).setPos(s1NewPos);
		(*s2).setPos(s2NewPos);
  	}
}

void setLimit(int n){
	LIMIT = n;
}  

}
