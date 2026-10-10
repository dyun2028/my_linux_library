#include <pthread.h>
#include <stdlib.h> //rands
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdatomic.h>

int glob = 0;
//pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
void* increase(void* arg) {
	int* v = (int*)arg;
	int cur = *v;
	for (int i = 0; i < 10; i++) {
		cur += 1;
	}

	int* n = malloc(sizeof(int));
	if (n == NULL) {
		return NULL;
	}
	*n = cur;
	return n;
}


int main(int argc, const char* argv[]) {
	srand((unsigned int)time(NULL));
	
	pthread_t my_thread;
	pthread_t my_thread2;
	pthread_t my_thread3;
	pthread_t my_thread4;
	//int* c;
	//*c = 0;
	int c = 5;
	int* p = malloc(sizeof(int));
	*p = 2;
	pthread_create(&my_thread, NULL, &increase, (void*)p);
	pthread_create(&my_thread2, NULL, &increase, (void*)p);
	pthread_create(&my_thread3, NULL, &increase, (void*)p);
	pthread_create(&my_thread4, NULL, &increase, (void*)p);
	/*
	int* temp;	
	pthread_join(my_thread, (void*)temp);
	if (temp != NULL) {
		int *temp2 = (int*)temp;
		c += *temp2;
		free(temp2);	
	}
	pthread_join(my_thread2, (void*)temp);
	if (temp != NULL) {
		int *temp2 = (int*)temp;
		c += *temp2;
		free(temp2);	
	}
	pthread_join(my_thread3, (void*)temp);
	if (temp != NULL) {
		int *temp2 = (int*)temp;
		c += *temp2;
		free(temp2);	
	}
	pthread_join(my_thread4, (void*)temp);
	if (temp != NULL) {
		int *temp2 = (int*)temp;
		c += *temp2;
		free(temp2);	
	}
	*/
	printf("%d\n", c);
	void* temp;	
	pthread_join(my_thread, &temp);
	if (temp != NULL) {
		int *temp2 = (int*)temp;
		c += *temp2;
		free(temp2);	
	}
	pthread_join(my_thread2, &temp);
	if (temp != NULL) {
		printf("Hi\n");
		int *temp2 = (int*)temp;
		c += *temp2;
		free(temp2);	
	}
	pthread_join(my_thread3, &temp);
	if (temp != NULL) {
		int *temp2 = (int*)temp;
		c += *temp2;
		free(temp2);	
	}
	pthread_join(my_thread4, &temp);
	if (temp != NULL) {
		int *temp2 = (int*)temp;
		c += *temp2;
		free(temp2);	
	}
	printf("%d\n", c);
}
