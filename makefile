CC=gcc
CFLAG = -fopenmp 

all: omp_solved2 omp_solved3 omp_solved4 omp_solved5 omp_solved6 jacobi-omp  gs-omp hw3writeup

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
	$(CC) $(CFLAG) jacobi-omp.c -o jacobi-omp -lm -lrt

gs-omp: gs-omp.c
	$(CC) $(CFLAG) gs-omp.c -o gs-omp -lm -lrt

hw3writeup: hw3writeup.tex
	latex hw3writeup.tex
	dvipdfm hw3writeup.dvi
 
clean:
	rm omp_solved2 omp_solved3 omp_solved4 omp_solved5 omp_solved6 jacobi-omp gs-omp *dvi *.pdf *.log *aux *.out
