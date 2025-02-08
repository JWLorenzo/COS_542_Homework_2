#include <stdio.h>
#include <pthread.h>
#define NumThreads 4
#define NumPoints 10000
#include <time.h>

int TotalHits = 0;
pthread_mutex_t MyMutex;
pthread_t ThreadID[NumThreads];

void *Compute(void*);

int main(){
	time_t start_t, end_t;
	double diff_t;
	int ret;
	int Count = NumPoints / NumThreads;
	time(&start_t);
	pthread_mutex_init(&MyMutex, NULL);
	for (int i=0; i < NumThreads; i++){
		ret = pthread_create(&ThreadID[i], NULL, Compute, (void*) &Count);
	}
	for (int i=0; i < NumThreads; i++){
		pthread_join(ThreadID[i],NULL);
	}
	time(&end_t);
	diff_t = difftime(end_t,start_t);
	printf("Time: %f",diff_t);
	return 0;
}

void *Compute(void *My_Count){
	int count = *( (int *) My_Count);
	int num_hits = 0;
	for (int i = 0; i < count; i++){
		// generate points
		// determine if in circle
		// if yes: inc num_hits
	
			
	}
	pthread_mutex_lock(&MyMutex);

	TotalHits += num_hits;		

	pthread_mutex_unlock(&MyMutex);

	return((void*)NULL);

}
