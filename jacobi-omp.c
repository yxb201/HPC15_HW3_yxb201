/*
 *
 *	Jacobi iteration to solve -u'' = 1
 *
 *
 *
 *	Yuan-Xun Bao
 *	Feb 12, 2015
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>




int main (int argc, char *argv[]){
	
	int N, j, Niter; 
	double  h, h2, f, r, r0, tol, rt;
	double *u, *unew;
	tol   = 1e-6;
	Niter = 0;
	clock_t t;
	
	if (argc != 2){
		fprintf(stderr, "must input discretization size N\n");
		exit(0);
	}
	
	N = atoi( argv[1] ) ;
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

	/* initial residual*/	
	r0 = 0.0;
	for(j=1; j<=N; j++){
		rt  = (-u[j-1] + 2.*u[j] - u[j+1]) / h2 - f;
		r0 += rt*rt;  
	}
	r0 = sqrt(r0/N);
	
	t = clock();	
	
	r = r0;
	while (r/r0 > tol){

		/* Jacobi iteration */
		for(j= 1; j <=N ; j++){
			unew[j] = (h2*f + u[j-1] + u[j+1] ) * 0.5;
		}
	
		/* copy work */
		for(j= 1; j <=N ; j++){
			u[j] = unew[j];
		}
	
		/* compute l2 residue */
		r = 0.0; 
		for(j=1; j <= N ; j++){
			rt = (-u[j-1] + 2.*u[j] - u[j+1]) / h2 - f;
			r += rt*rt; 	
		}
		r = sqrt(r/N);
		Niter++;

//		printf("the residual at %dth iterion is %.14f\n",Niter, r);
	}
	
	t = clock() - t;	

	printf("Total number of iterations is %d\n", Niter);
	printf("Time elapsed is %f seconds.\n", ((float)t/CLOCKS_PER_SEC));
	
	free(u); free(unew);	
	
	return 0;
}
