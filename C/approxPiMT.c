#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <sys/time.h>  
  
  
  //compile with my exe: a.o b.o c.o d.o	gcc -o myexe a.o b.o c.o d.o(ou $^)
  //a.o: a.c	gcc -c a.c
  
  //%.o: %.		gcc -c $^
  
  
  //name for the file is makefile
  
  //program make

int R = 1;
int nPoints;
int nThreads;

	
//Thread function get an argument and return something - void * means any type
void *f(void *arg) 
{ 	
	
	int* partial_in = malloc(sizeof(int*));	
	*partial_in  = 0;
	struct timeval tv;
	unsigned int seed;
	
	int i;
	for(i=0; i < nPoints/nThreads; i++){
			
		gettimeofday(&tv, NULL);
		seed = 10000000000 * tv.tv_sec + tv.tv_usec;
		double x = (double)rand_r(&seed) / (double) RAND_MAX;
		double y = (double)rand_r(&seed) / (double) RAND_MAX;
	
		if(x*x + y*y < 1){
			*partial_in+=1;
		}

	}
    pthread_exit((void*)(partial_in)); 
} 


//gcc -pthread -o approxPiMT approxPiMT.c
int main(int argc, char **argv)
{
	int i, total_in;
	void* t_return_value;

	nPoints = atoi(argv[1]);
	nThreads = atoi(argv[2]);

	pthread_t* threads = malloc(sizeof(pthread_t) * nThreads);

	for(i = 0; i < nThreads; i++){
		pthread_create(&threads[i], NULL, f, NULL);
	}
	
	
	for(i = 0; i < nThreads; i++){
		pthread_join(threads[i], &t_return_value);
		total_in += *(int*)t_return_value;
	}
	
	
	double pi = 4.0*((double)total_in/(double)nPoints);
	//printf("\n%d,%d,%f", nPoints, nThreads, pi);
	
    exit(0); 
}

   

