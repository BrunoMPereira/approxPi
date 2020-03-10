#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
  
  
  //compile with my exe: a.o b.o c.o d.o	gcc -o myexe a.o b.o c.o d.o(ou $^)
  //a.o: a.c	gcc -c a.c
  
  //%.o: %.		gcc -c $^
  
  
  //name for the file is makefile
  
  //program make

int nPoints;
int nThreads;


float r(unsigned int seed)
{	
    return (double)rand_r(&seed) / (double)RAND_MAX ;
}

static int isInsideCircle(float x, float y){
	return x*x + y*y <= 1;	
}

	
//Thread function get an argument and return something - void * means any type
void *f(void *arg) 
{ 	
	
	int* countInside = malloc(sizeof(int*));
	int i;
	unsigned int seed = time(NULL);
	for(i=0; i<nPoints/nThreads;i++){
		
		seed++;
		if(isInsideCircle(r(seed), r(seed))){
			(*countInside)++;
			//printf("%d\n", *countInside);
		}
	}
	
    return (void *) countInside; 
} 


//gcc -pthread -o approxPiMT approxPiMT.c
int main(int argc, char **argv)
{
	nPoints = atoi(argv[1]);
	nThreads = atoi(argv[2]);
	
	pthread_t tid;
	
	pthread_create(&tid, NULL, f, NULL);
	
	void* partial_count_inside;
	
	pthread_join(tid, &partial_count_inside);
	
	
	int countInside = 0;
	countInside = *(int *)partial_count_inside;
	
	printf("\nTotal Number of points: %d", nPoints);
	printf("\nPoints within circle: %d", countInside);
	
	double pi = (countInside/nPoints);
	printf("\nPi estimation: %f\n\n", pi);
	
    exit(0); 
}

   

