CC=gcc
CFLAG = -fopenmp 

all: omp_solved2 omp_solved3 omp_solved4 omp_solved5 omp_solved6 jacobi-omp

omp_solved2: omp_solved2.c
	$(CC) $(CFLAG) omp_solved2.c -o omp_solved2

omp_solved3: omp_solved3.c
	$(CC) $(CFLAG) omp_solved3.c -o omp_solved3

omp_solved4: omp_solved4.c
	$(CC) $(CFLAG) omp_solved4.c -o omp_solved4

omp_solved5: omp_solved5.c
	$(CC) $(CFLAG) omp_solved5.c -o omp_solved5

omp_solved6: omp_solved6.c
	$(CC) $(CFLAG) omp_solved6.c -o omp_solved6

jacobi-omp: jacobi-omp.c
	$(CC) $(CFLAG) jacobi-omp.c -o jacobi-omp -lm -O3

clean:
	rm omp_solved2 omp_solved3 omp_solved4 omp_solved5 omp_solved6 jacobi-omp
