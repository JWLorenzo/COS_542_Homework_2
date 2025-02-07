#include <stdio.h>
#include <pthread.h>
#define NumThreads 4
#define NumPoints 10000

int TotalHits = 0;

pthread_mutex_t My_Mutex;
pthread_t ThreadID[NumThreads];

void *Compute(void*);

int main(){
	printf("Hello_World");
	return 0;
}

void *Compute(void *My_Count){}
