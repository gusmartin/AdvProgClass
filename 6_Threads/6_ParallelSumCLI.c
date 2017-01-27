/**
 * Copyright (c) 2015 Abelardo López Lagunas
 *
 * @file    6_ParallelSumCLI.c
 *
 * @author  Abelardo López Lagunas
 *
 * @date    Wed Mar 30 15:09:11 CST 2016
 *
 * @brief   Implements a command line version of the optimized parallel
 *          sum to show how to instrument a program for future profiling.
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

/* Define the expected number of parameters */
const unsigned int NUMPARAMS  = 2;

/*
 * The range size should be read-only but can't be a constant since its
 * value is known at run time. So special care must be taken not to change
 * its value.
 */
unsigned int range;

/*
 * Each thread computes a partial sum and returns it when the thread
 * ends execution. This is more efficient since the pthread join already
 * synchronizes waiting for thread termination.
 */
void *thread_function(void *arg) {

	unsigned int index;  /* Encodes the range that will be computed */
	unsigned int * sum;  /* The partial sum resides in the heap to avoid
	                      * problems when returning a pointer to it */

	index = *((unsigned int *) (arg)); /* Value from the parameter */

	/* Allocate memory for the partial result & check its valid */
	sum = (unsigned int *) malloc (sizeof(unsigned int));
	assert(sum != NULL);

	/* Calculate the sum from index*range until ((index+1)*range)-1 */
  	for ( unsigned int i = index * range; i < ((index+1)*range); i++ )
  		*sum += i;

#ifdef DEBUG
   	printf ("The partial sum for thread %u is %u\n", index, *sum);
#endif

  pthread_exit ((void *)sum);
}

/* The main program follows the boss-worker model. Read two parameters
 * from the command line, the number of threads and the upper limit of
 * the sum that we want to compute.
 */
int main(int argc, const char * argv[]) {

  unsigned int   sumTotal = 0;           /* Accumulate the final result */
  pthread_t    * mythreads;                  /* Pointer to thread array */
  unsigned int * threadName;            /* Pointer to the "names" array */
  unsigned int * partial;                /* Partial sum from the thread */
  unsigned int   MAXTHREADS;                     /* # of worker threads */
  unsigned int   UPPERLIMIT;                  /* Upper limit of the sum */
  unsigned int   rmdr;                    /* Sum to be done by the boss */

  /* Start by checking that the parameters are correct */
  assert (argc == NUMPARAMS + 1);
  MAXTHREADS = atoi(argv[1]);    /* First parameter is the # of threads */
  UPPERLIMIT = atoi(argv[2]);    /* Second parameter is the upper limit */

  assert (MAXTHREADS > 1);
  assert (UPPERLIMIT > 1);

#ifdef DEBUG
  printf("Will compute the sum from 0 to %u with %u threads\n",
	     UPPERLIMIT-1, MAXTHREADS);
#endif

/* The range must be calculated somehow */
  range = UPPERLIMIT / MAXTHREADS;
  rmdr  =  UPPERLIMIT % MAXTHREADS;

  mythreads = (pthread_t *) malloc (sizeof (pthread_t) * MAXTHREADS);
  assert(mythreads != NULL);

  threadName = (unsigned int *) malloc (sizeof(unsigned int)*MAXTHREADS);
  assert(threadName != NULL);


/* Start by spawning all the threads */
  for (unsigned int i = 0; i < MAXTHREADS; i++){
     threadName[i] = i;
     if (pthread_create(&mythreads[i], NULL, thread_function,
         &threadName[i]) != 0)
		perror ("error creating thread.");
  }

#ifdef	DEBUG
	printf ("The last range goes from %u to %u\n",
	         UPPERLIMIT - rmdr - 1, UPPERLIMIT-1);
#endif

/* Calculate the sum from the last index*range */
  for ( unsigned int i = UPPERLIMIT - rmdr; i < UPPERLIMIT; i++ )
  	sumTotal += i;

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

      free (partial);     /* De-allocate the heap space for the result */
    }

  printf("\nThe total sum equals %u\n",sumTotal);

  free(mythreads);
  free(threadName);
  return 0;
}
