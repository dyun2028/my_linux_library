#include <pthread.h>
#include <stdlib.h> //rands
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdatomic.h>

int glob = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
void* increase(void* arg) {
	//int* c = (int *)arg;	

	for (int i = 0; i < 1000000; i++) {
//		int delay = 1000 + rand() % 999000;
//		printf("%d\n", i);
	//	usleep(delay);
		//pthread_mutex_lock(&lock);
		glob += 1;
		//pthread_mutex_unlock(&lock);
	}
	//(*c)++;
	//printf("hello, %d", *c);
}


int main(int argc, const char* argv[]) {
	srand((unsigned int)time(NULL));
	
	pthread_t my_thread;
	pthread_t my_thread2;
	pthread_t my_thread3;
	pthread_t my_thread4;
	//int* c;
	//*c = 0;
	pthread_create(&my_thread, NULL, &increase, NULL);
	pthread_create(&my_thread2, NULL, &increase, NULL);
	pthread_create(&my_thread3, NULL, &increase, NULL);
	pthread_create(&my_thread4, NULL, &increase, NULL);
	pthread_join(my_thread, NULL);
	pthread_join(my_thread2, NULL);
	pthread_join(my_thread3, NULL);
	pthread_join(my_thread4, NULL);
	printf("%d\n", glob);
}
