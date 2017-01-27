/**
 * Copyright (c) 2015 Abelardo López Lagunas
 *
 * @file    5_ParallelSumImproved.c
 *
 * @author  Abelardo López Lagunas
 *
 * @date    Wed Mar 30 15:09:11 CST 2016
 *
 * @brief   Shows how to synchronize when sharing data across threads
 *
 * References:
 *          The code was made up to show how a share memory, and use
 *          pthread_join to synchronize access to it.
 *
 * Restrictions:
 *          There is no validation in the code
 *
 * Revision history:
 *          Wed Mar 30 15:09:11 CST 2016 -- File modified to add comments.
 *
 * @note    Used for the TC2025 class
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>                         // For thread management
#include <assert.h>                          // For assertion management

/* Define the maximum number of threads as a constant */
const unsigned int MAXTHREADS=4;

/*
 * Each thread computes a partial sum and returns it when the thread
 * ends execution. This is more efficient since the pthread join already
 * synchronizes waiting for thread termination.
 */
void *thread_function(void *arg) {

	unsigned int index;   /* Encodes the range that will be computed */
	unsigned int * sum;   /* Partial sum must reside in the heap to avoid
	                       * problems when returning a pointer to it */

	index = *((unsigned int *) (arg)); /* Index from the parameter */

	/* Allocate memory for the partial result & check its valid */
	sum = (unsigned int *) malloc (sizeof(unsigned int));
	assert(sum != NULL);

	/* Calculate the sum from index*25 until ((index+1)*25)-1 */
	for ( unsigned int i = index * 25; i < ((index+1)*25); i++ )
  		*sum += i;

#ifdef DEBUG
   		printf ("The partial sum is %u\n", *sum);
#endif

	  pthread_exit ((void *)sum);
}

/* The main program follows the boss-worker model */
int main(void) {

  unsigned int sumTotal = 0;           /* Accumulate the final result */
  pthread_t mythreads[MAXTHREADS];                   /* Threads array */
  unsigned int threadName[MAXTHREADS]; /* Thread "names" are integers */
  unsigned int * partial;              /* Partial sum from the thread */

  /* Start by spawning all the threads */
  for (unsigned int i = 0; i < MAXTHREADS; i++){
  	threadName[i] = i;
  	if (pthread_create(&mythreads[i], NULL, thread_function,
    	  &threadName[i]) != 0)
		perror("error creating thread.");
  	}

/* In the boss-worker model the boss does no actual work, just waits for
 * the workers to finish.
 */
  for (unsigned int i = 0; i < MAXTHREADS; i++){
  /* pthread_join expects a handle so do some typecasting */
    if (pthread_join ( mythreads[i], (void **)&partial) != 0)
	  perror("error joining thread.");

    sumTotal += *partial;

#ifdef	DEBUG
	printf ("The running sum is %u\n", sumTotal);
#endif

    free (partial);        /* De-allocate the heap space for the result */
    }

  printf("\nThe total sum equals %u\n",sumTotal);
  return 0;
}
