/**
 * Copyright (c) 2015 Abelardo López Lagunas
 *
 * @file    4_ParallelSum.c
 *
 * @author  Abelardo López Lagunas
 *
 * @date    Wed Mar 30 14:48:13 CST 2016
 *
 * @brief   Shows how to use a Mutex when sharing data across threads
 *
 * References:
 *          The code was made up to show how a mutex could be used to
 *          control the access to shared memory, it is not optimized
 *          since the cost of synchronization is larger than
 *          the time spent in the critical region.
 *
 * Restrictions:
 *          There is no validation in the code
 *
 * Revision history:
 *          Wed Mar 30 14:48:13 CST 2016 -- File modified to add comments.
 *
 * @note    Used for the TC2025 class
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>                          // For thread management

// Use #define for the number of threads to remove a warning
#define MAXTHREADS 4

int sumTotal;                  // Declare global constants and the Mutex.
pthread_mutex_t mymutex=PTHREAD_MUTEX_INITIALIZER;

/*
 * Thread function receives an integer id as argument, stores partial sum
 * in a global variable protected with a Mutex
 */
void *thread_function(void *arg) {

unsigned int index;
unsigned int sum = 0;

index = *((unsigned int *) (arg));

/* Calculate the sum from index*25 until ((index+1)*25)-1 */
  for ( unsigned int i = index * 25; i < ((index+1)*25); i++ )
  	sum += i;

   /*
    * Note that the cost of synchronization is higher than the actual
	* computation for this example, so we need to improve it (see the
	* improved implementation 5_ParallelSumImproved.c
	*/
   	pthread_mutex_lock(&mymutex);
	   sumTotal += sum;
	pthread_mutex_unlock(&mymutex);

  	return NULL;
}

/* Main entry point creates several threads and assigns them a unique id */
int main(void) {
  pthread_t mythreads[MAXTHREADS];
  unsigned int threadName[MAXTHREADS];

  /* Create the threads */
  for (unsigned int i = 0; i < MAXTHREADS; i++){

  	threadName[i] = i;

  	if (pthread_create(&mythreads[i], NULL, thread_function,
    	  &threadName[i]) != 0)
		perror("error creating thread.");

  }

  /* Now wait for them in-order, this is inefficient */
  for (unsigned int i = 0; i < MAXTHREADS; i++){
    if (pthread_join ( mythreads[i], NULL ) != 0)
	  perror("error joining thread.");

  }

  printf("\nThe total sum equals %u\n",sumTotal);
  return 0;
}
