CC=gcc-4.9
CFLAG = -fopenmp 

all: omp_solved2 omp_solved3 omp_solved4 omp_solved5 omp_solved6

omp_solved2: omp_solved2.c
	$(CC) $(CFLAG) omp_solved2.c -o omp_solved2

omp_solved3: omp_solved3.c
	$(CC) $(CFLAG) omp_solved3.c -o omp_solved3


clean:
	rm omp_solved2 omp_solved3
