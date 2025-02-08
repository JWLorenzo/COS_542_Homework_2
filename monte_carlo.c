#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NumThreads 4
#define NumPoints 100000000
#include <time.h>

int TotalHits = 0;
pthread_mutex_t MyMutex;
pthread_t ThreadID[NumThreads];

void *Compute(void*);

double SquareNum (double a){
	return a * a;
}


double RandDouble (double max, double min){
	
	double RandNum = (double) rand(); //Generates a random int between 0 and RAND_MAX then typecasts to a double
	double Normalize = RandNum / (double)RAND_MAX; //Divides by rand max to get it into range of (0,1.0)
	double ShiftRange = Normalize * (max-min) + min; //Shifts range to (min,max)
	
	return ShiftRange;

}

int main(){
	
	time_t start_t, end_t;
	double diff_t;
	int ret;
	int Count = NumPoints / NumThreads;
	
	time(&start_t);
	srand (time(NULL));
	pthread_mutex_init(&MyMutex, NULL);
	
	for (int i=0; i < NumThreads; i++){
		ret = pthread_create(&ThreadID[i], NULL, Compute, (void*) &Count);
	}
	for (int i=0; i < NumThreads; i++){
		pthread_join(ThreadID[i],NULL);
	}
	
	double PiApprox = ((double)TotalHits/ (double)NumPoints) * 4;
	
	printf("%lf\n", PiApprox);
	
	time(&end_t);
	diff_t = difftime(end_t,start_t);
	
	printf("Time: %lf\n",diff_t);
	
	return 0;
}

void *Compute(void *My_Count){
	int count = *( (int *) My_Count);
	int num_hits = 0;
	
	for (int i = 0; i < count; i++){
	
		double randomX = RandDouble(1.0,-1.0);
		double randomY = RandDouble(1.0,-1.0);

		if ((SquareNum(randomX) + SquareNum(randomY)) <= 1){
			num_hits += 1;
		}		
			
	}
	
	pthread_mutex_lock(&MyMutex);

	TotalHits += num_hits;		
	
	pthread_mutex_unlock(&MyMutex);

	return((void*)NULL);

}
