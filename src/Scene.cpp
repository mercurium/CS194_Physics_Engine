#include "Scene.h"
#include <omp.h>

Scene::Scene(){
	numBalls = 100;
	twoD = false;
    GRID_SIZE = 10;
	//balls = makeTestScene();
	//distConstr = makeTestDistConstr(balls);
}


Scene::Scene(Sphere* ballList, DistConstr* constraints, int balls_size, int constraints_size){
    GRID_SIZE = 100;
	balls = ballList;
	distConstr = constraints;
	numBalls = balls_size;
	numConstr = constraints_size;
	GRID_COL_SIZE = 3 * numBalls / (GRID_SIZE * GRID_SIZE);
}

/*
std::vector <Sphere *> Scene::makeTestScene(){
	std::vector <Sphere *> ballList;
	double x,y,z;
	for (int i = 0; i < this->numBalls; i++){
		x = ((i*i + 3*i+504)%2011 + i/200.)/10.;
		y = ((2*i*i - i + 1017)%2011 + i/200.)/10.;
		if (!this->twoD)
			z = ((5*i*i - 13 *i + 1014) % 2011 + i/200.)/10.;
		else
			z = 0;
		ballList.push_back(new Sphere(x,y,z,this->twoD));

	}
	return ballList;
}

std::vector <DistConstr *> Scene::makeTestDistConstr(std::vector <Sphere *> balls){
       std::vector <DistConstr *> distConstr;
       for(int n = 0; n < balls.size() /4; n++){
               for(int i = 1; i < 4; i++){
                       for (int j = 0; j < i; j++){
                               distConstr.push_back(new DistConstr(balls.at(4*n+i),balls.at(4*n+j),2.01));
							   balls.at(4*n+j)->setColor(balls.at(4*n+i)->getColor());
                       }
               }
       }
       return distConstr;
}
*/

void Scene::UpdateScene(double time){
    Physics::UpdateBallPositions((this->balls), this->numBalls, time);
    Physics::UpdateBallBoundaries(this->balls, this->numBalls);
    for(int i = 0; i < 5; i++){
    	Intersection** intersections;
        intersections = getCollisions();
        Physics::resolveCollisions(intersections, this->numCollisions);
    	Physics::UpdateBallBoundaries(this->balls, this->numBalls);
    }
}

Sphere* Scene::getBalls(){
	return this->balls;
}

/*
std::vector<Intersection *> Scene::getCollisions(){
   
	std::vector<Intersection *> intersects;

	std::vector <Sphere *> list_of_balls[GRID_SIZE * GRID_SIZE];
	for(int i = 0; i < balls.size(); i++){
		Sphere *s = balls.at(i);
		int x = s->getPos().x / (100/GRID_SIZE);
		x = std::min(std::max(x,0),GRID_SIZE-1);
		int z = s->getPos().z / (100/GRID_SIZE);
		z = std::min(std::max(z,0),GRID_SIZE-1);
		list_of_balls[x * GRID_SIZE + z].push_back(s);
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
  
	std::vector<Intersection *> intersects;
	for(int i = 1; i < balls.size(); i++){ //First compute all the intersections that happen
		for(int j = 0; j < i; j++){
			double dist = glm::distance(balls.at(i)->getPos(), balls.at(j)->getPos());
			double radiiDist = balls.at(i)->getRadius() + balls.at(j)->getRadius();
			if (dist < radiiDist-.001){ // .001 to avoid rounding error
				intersects.push_back(new Intersection(balls.at(i),balls.at(j)));
			}
		}
	}
    return intersects;
}
*/

Intersection** Scene::getCollisions(){
	const int colsize = GRID_COL_SIZE;

	struct column{
		Sphere** col; //upper bound
		int size;
	};

    int col_size[GRID_SIZE*GRID_SIZE];
	#pragma omp parallel for
	for(int i = 0; i < (GRID_SIZE*GRID_SIZE); i++){
        col_size[i] = 0;
    }

	#pragma omp parallel for
	for(int i = 0; i < this->numBalls; i++){
		Sphere *s = &balls[i];
		glm::detail::fvec4SIMD pos = s->getPos();
		glm::vec4 posVec4 = glm::vec4_cast(pos);

		int x = posVec4.x / (100/GRID_SIZE);
		x = std::min(std::max(x,0), GRID_SIZE-1);
		int z = posVec4.z / (100/GRID_SIZE);
		z = std::min(std::max(z,0), GRID_SIZE-1);

		col_size[x*GRID_SIZE+z]++;
	}

	Intersection** intersects = new Intersection*[numBalls * 30]; //upperbound
	numCollisions = 0;

	column list_of_balls[GRID_SIZE * GRID_SIZE];

	#pragma omp parallel for
	for(int i = 0; i < (GRID_SIZE*GRID_SIZE); i++){
    //printf("Allocating arr size: %d\n", col_size[i]);
       list_of_balls[i].col = new Sphere*[col_size[i]]; 
       list_of_balls[i].size = 0;
    }

	#pragma omp parallel for
	for(int i = 0; i < this->numBalls; i++){
	
		Sphere *s = &balls[i];
		glm::detail::fvec4SIMD pos = s->getPos();
		glm::vec4 posVec4 = glm::vec4_cast(pos);
		//column* col_ptr = NULL;

		int x = posVec4.x / (100/GRID_SIZE);
		x = std::min(std::max(x,0), GRID_SIZE-1);
		int z = posVec4.z / (100/GRID_SIZE);
		z = std::min(std::max(z,0), GRID_SIZE-1);
		
		int size = list_of_balls[x*GRID_SIZE+z].size;

		list_of_balls[x*GRID_SIZE+z].col[size] = s;
		list_of_balls[x*GRID_SIZE+z].size++;
	}

    //new intersects array for each thread
    //printf("a %d\n", omp_get_num_threads());
    //fflush(stdout);
    int nthreads = omp_get_max_threads();//omp_get_num_threads();
    int thr_num_col[nthreads];
	#pragma omp parallel for
	for(int i = 0; i < (nthreads); i++){
        thr_num_col[i] = 0;
    }
    Intersection* thr_intersects[nthreads * (numBalls*20)];

	#pragma omp parallel for
	for (int i = 0; i < GRID_SIZE; i++){
        int tid = omp_get_thread_num();
		for(int ii = 0; ii <= 1; ii++){
			if (i+ii < 0 || i+ii >= GRID_SIZE){ continue; }

			for (int j = 0; j < GRID_SIZE; j++){
				for (int jj = 0; jj <= 1; jj++){
					if (jj+j < 0 || jj+j >= GRID_SIZE){ continue; }

					int p1 = GRID_SIZE * i + j, p2 = GRID_SIZE * (i+ii) + j + jj;

					for(int b1 = 0; b1 < list_of_balls[p1].size; b1++){
						for(int b2 = 0; b2 < list_of_balls[p2].size; b2++){
							if (p1 == p2 && b1 <= b2){ continue; }
							
							double dist = glm::distance((*list_of_balls[p1].col[b1]).getPos(), (*list_of_balls[p2].col[b2]).getPos());
							double radiiDist = (*list_of_balls[p1].col[b1]).getRadius() + (*list_of_balls[p2].col[b2]).getRadius();
							if (dist < radiiDist-.001){ // .001 to avoid rounding error
								//intersects[numCollisions++] = new Intersection(list_of_balls[p1].col[b1], list_of_balls[p2].col[b2]);
                                thr_intersects[(tid)*nthreads+thr_num_col[tid]] = new Intersection(list_of_balls[p1].col[b1], list_of_balls[p2].col[b2]);

                                thr_num_col[tid]++;
                                numCollisions++;
							}
						}
					}
				}
			}		
		}
    }

    //printf("startidx: ");
    //fflush(stdout);
    //scan across thr_num_collisions
    int start_idx[nthreads];
    start_idx[0] = 0;
    for(int i=1; i<nthreads; i++){
        start_idx[i] = start_idx[i-1]+thr_num_col[i-1];
        //printf("%d ", start_idx[i]);
    }
    //printf("\n");
    //fflush(stdout);
    
    //reduce intersection lists into a single array
    int ncol = 0;
    #pragma omp parallel for
    for(int i=0; i<nthreads; i++){
        int tid = omp_get_thread_num();
        int num_col = thr_num_col[tid];
        for(int j=0; j< num_col; j++){
            intersects[ start_idx[tid]+j] = thr_intersects[tid*nthreads+j]; 
            #pragma omp critical
            {
                ncol++;
            }
        }
    }
    for(int i = 0; i < (GRID_SIZE*GRID_SIZE); i++){
       delete list_of_balls[i].col;
    }

    return intersects;
}
