/*
 *
 *
 *	Gauss-Seidal to solve -u'' = 1
 *
 *	Parallel using OpenMP
 *
 *	April 13, 2015
 *	Yuanxun Bao	
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include "util.h"


int main (int argc, char *argv[]){
	
	int N, i, j; 
	double  h, h2, f, r, r0, rt, tol;
//	tol = 1e-6;
	double *u;
	int MAX_ITER;

	if (argc != 3){
		fprintf(stderr,"must input discretization size N and # of iterations");
		exit(0);
	}
	
	// parse N
	N = atoi( argv[1] ) ;
	MAX_ITER = atoi( argv[2] );
	h = 1./(N+1); h2 = h*h;
	f = 1.;

	/* GS, one array */
	u = malloc( (N+2) * sizeof(double));

 	/* initialize */
	for(j = 0; j<=N+1; j++){
		u[j] = 0.;
	}

/*	
	// initial residual
	r0 = 0.0;
	for(j=1; j <= N ; j++){
		rt = (-u[j-1] + 2.*u[j] - u[j+1]) / h2 - f;
		r0 += rt*rt; 	
	}
	r0 = sqrt(r0/N);
*/

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


	for(i=0; i<MAX_ITER; i++){
		
		
		// gauss-seidal iteration

#pragma omp parallel for private(j)	
		// 1st sweep
		for(j= 1; j <= N/2 ; j++){
			u[j] = (h2*f + u[j+(N/2)] + u[j+1+(N/2)] ) * 0.5;
		}

#pragma omp parallel for private(j)
		// 2nd sweep
		for(j= 1; j<=N/2; j++){
			u[j+N/2] = (h2*f + u[j-1] + u[j] ) * 0.5;
		}

/*
		// compute l2 residue 
		r = 0.0;
		for(j=1; j <= N/2 ; j++){
			rt = (2.*u[j] - u[j+(N/2)] - u[j+1+(N/2)]) / h2 - f;
			r +=  rt*rt; 	
		}
		for(j=1; j<= N/2 ; j++){
			rt = (-u[j-1]-u[j] + 2.*u[j+N/2]) / h2 - f;
			r += rt*rt;
		}
		r = sqrt(r/N);
		Niter++;

		printf("the residual at %dth iterion is %.14f\n",Niter, r);
*/
	}
	
	get_timestamp(&stop_t);
	double elapsed = timestamp_diff_in_seconds(start_t, stop_t);

	printf("Total number of iterations is %d\n", MAX_ITER);
	printf("Time elapsed is %f seconds.\n ", elapsed);

	free(u);	
	
	return 0;
}
