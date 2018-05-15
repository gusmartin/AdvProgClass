#include <stdio.h>
#include<pthread.h>
#include <unistd.h>                  // For the sleep function
#include <stdlib.h>

#define BUFFER_SIZE 4
#define LIMIT (-1)
#define COUNT 11

int flag = 0;

struct prodcons {
	
	int buffer[BUFFER_SIZE]; 	// Data to store
	pthread_mutex_t key; 		// Synchronization variable
	pthread_mutex_t barberReady; // mutex
	pthread_mutex_t custReady; // mutex
	int read, write;			// Read/ Write position
	pthread_cond_t notEmpty;	// Signal buffer NOT empty
	pthread_cond_t notFull;		// Signal buffer NOT full
	
} buffer;

void init(struct prodcons * b){
	
	pthread_mutex_init(&b->key, NULL);
	pthread_mutex_init(&b->barberReady, NULL);
	pthread_mutex_init(&b->custReady, NULL);
	pthread_cond_init(&b->notEmpty, NULL);
	pthread_cond_init(&b->notFull, NULL);
	b->read = 0;
	b->write = 0;
	
}

//This is the Customer
void * Producer(void * data){
	
	int n = *((int*)data);
	
	struct prodcons *b = &buffer;
	
 	sleep(rand() % BUFFER_SIZE);

	pthread_mutex_lock(&b->key);// wait to get the lock
	
	// If buffer(chairs) is full then ext the store instead of waiting
	//printf("%d - rr %d write %d\n",data,b->write + b->read, b->write);
	
	if((b->write + b->read) == 4){
		//pthread_cond_wait(&b->notFull, &b->key);
		printf("%d - no chairs available!\n", n);
		pthread_mutex_unlock(&b->key);
		return 0;
	}
		
	if(b->write >= BUFFER_SIZE)
		b->write = 0;
	
	b->buffer[b->write] = n;
	b->write++;
	
	printf("%d - Seated\n", n);
	
	

	flag++;
	pthread_cond_signal(&b->notEmpty); // check this notEmpty
	pthread_mutex_unlock(&b->key);
	
	//sleep(1);
	
	//pthread_cond_wait(&b->notFull, &b->barberReady);

	//printf("%d - Served\n", n);
	
	return NULL;
}

// This is the barber
void * Consumer(void * data){
	
	struct prodcons *b = &buffer;
	
	while(1){
		
		int n;
				
		//printf("in - flag = %d\n", flag);
		
		while(!flag){
			pthread_cond_wait(&b->notEmpty, &b->custReady); // wait till a customer arrives
		
		}
		flag--;
		//printf("in\n");
		
		pthread_mutex_lock(&b->key);
		
		n = b->buffer[b->read];
		b->read++;
		if(b->read >= BUFFER_SIZE)
			b->read = 0;
			
		printf("%d - Cutted hair\n", n);
		
		//pthread_cond_signal(&b->notFull);
		pthread_mutex_unlock(&b->key);
		
	}
	
	return NULL;
}

int main(void){
	
	pthread_t th_a, th_b, th_c, th_d, th_e, th_f, th_g, th_h, th_i, th_j;
	void  * returnValue;
	
	int number[10] = {0,1,2,3,4,5,6,7,8,9};
	
	init(&buffer);
	pthread_create(&th_a, NULL, Consumer, NULL);
	pthread_create(&th_b, NULL, Producer, &number[1]);
	pthread_create(&th_c, NULL, Producer, &number[2]);
	pthread_create(&th_d, NULL, Producer, &number[3]);
	pthread_create(&th_e, NULL, Producer, &number[4]);
	pthread_create(&th_f, NULL, Producer, &number[5]);
	pthread_create(&th_g, NULL, Producer, &number[6]);
	pthread_create(&th_h, NULL, Producer, &number[7]);
	pthread_create(&th_i, NULL, Producer, &number[8]);
	pthread_create(&th_j, NULL, Producer, &number[9]);
	
	pthread_join(th_a, &returnValue);
	pthread_join(th_b, &returnValue);
	pthread_join(th_c, &returnValue);
	pthread_join(th_d, &returnValue);
	pthread_join(th_e, &returnValue);
	pthread_join(th_f, &returnValue);
	pthread_join(th_g, &returnValue);
	pthread_join(th_h, &returnValue);
	pthread_join(th_i, &returnValue);
	pthread_join(th_j, &returnValue);
	
	return 0;
}
