/*
 *
 *	Jacobi iteration to solve -u'' = 1
 *
 *      parallelize using OpenMP
 *
 *	Yuan-Xun Bao
 *	April 20, 2015
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include "util.h"


int main (int argc, char *argv[]){
	
	int N, i, j; 
	double  h, h2, f, r, r0, tol, rt;
	double *u, *unew;
	int MAX_ITER;

	if (argc != 3){
		fprintf(stderr, "must input discretization size N and # of iterations\n");
		exit(0);
	}
	
	N = atoi( argv[1] );
	MAX_ITER = atoi( argv[2] );
	h = 1./(N+1); h2 = h*h;
	f = 1.;

	/* Jacobi, two arrays */
	u    = (double *) malloc( (N+2) * sizeof(double));
	unew = (double *) malloc( (N+2) * sizeof(double));

 	/* initialize */
	for(j = 0; j<=N+1; j++){
		u[j]    = 0.;
		unew[j] = 0.;
	}

        /* initial residual */	
	r0 = 0.0;
	for(j=1; j<=N; j++){
		rt  = (-u[j-1] + 2.*u[j] - u[j+1]) / h2 - f;
		r0 += rt*rt;  
	}
	r0 = sqrt(r0/N);

	#pragma omp parallel
	{
		printf("Hello, I am thread %d of %d\n", 
			omp_get_thread_num(), 
			omp_get_num_threads());
	}

	timestamp_type start_t, stop_t;	
	get_timestamp(&start_t);

//	r = r0;
//	while (r/r0 > tol){
	
	for(i = 0; i < MAX_ITER; i++ ){
		       
#pragma omp parallel for default(none) \
			 schedule(static) \
			 shared(u,unew,h2,f,N)
		//jacobi iteration
		for(j= 1; j <=N ; j++){
			unew[j] = (h2*f + u[j-1] + u[j+1] ) * 0.5;
		}
	//	printf("Thread %d done\n", omp_get_thread_num());		

		
#pragma omp parallel for default(none) \
			 schedule(static) \
			 shared(u,unew,h2,f,N)
		// copy work 
		for(j= 1; j <=N ; j++){
			u[j] = unew[j];
		}
/*
 		r = 0.0;
		// compute residual
		for(j=1; j <= N ; j++){
			rt = (-u[j-1] + 2.*u[j] - u[j+1]) / h2 - f;
			r = r + rt*rt; 	
		}

		r = sqrt(r/N);		
*/		
//		printf("the residual at %dth iteration is %.14f\n", i+1, r);
	}

	get_timestamp(&stop_t);
	double elapsed = timestamp_diff_in_seconds(start_t, stop_t);
	
	printf("Total number of iterations is %d\n", MAX_ITER);
	printf("Time elapsed is %f seconds.\n", elapsed);
//	printf("the residual at %dth iteration is %.14f\n", MAX_ITER, r);
	
	free(u); free(unew);	
	
	return 0;
}
