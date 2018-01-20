/**
 * Copyright (c) 2015 Abelardo López Lagunas
 *
 * @file    3_Mutex.c
 *
 * @author  Abelardo López Lagunas
 *
 * @date    Wed Mar 30 14:48:13 CST 2016
 *
 * @brief   Shows how to use a Mutex in pthreads
 *
 * References:
 *          The code was made up to show how a mutex could be used, it is
 *          not optimized since the cost of synchronization is larger than
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
#include <unistd.h>             // For sleep function
#include <pthread.h>            // For thread management

/* Mutexes are used to share global data, so a Mutex must also be global */
int myglobal = 0;
pthread_mutex_t mymutex=PTHREAD_MUTEX_INITIALIZER;

/* The threads receive no arguments */
void *thread_function(void *arg) {
  int i;
  for ( i=0; i<20; i++ ) {
	/*
	 * Note that  the mutex is needed to access the
	 * shared variable myglobal.
	 */
	pthread_mutex_lock(&mymutex);
	  myglobal++;
	  printf(".");
	  fflush(stdout);           // Make sure printf outputs its buffer
	  sleep(1);
	pthread_mutex_unlock(&mymutex);
  }
  return NULL;
}

int main(void) {
  pthread_t mythread;
  int i;

  if (pthread_create(&mythread, NULL, thread_function, NULL)){
	printf("error creating thread.");
	abort();
  }

  for ( i=0; i<20; i++) {
  	/*
  	 * Can use try_lock instead of lock of the thread wants to do useful
  	 * work instead of blocking when the lock is not available.
  	 *
       while(pthread_mutex_trylock(&mymutex)){
       printf("|");     // Show waiting thread, this may be too noisy
        fflush(stdout);  // at the output
     }
	*/
    pthread_mutex_lock(&mymutex);
      myglobal++;
      printf("-");
      fflush(stdout);           // Make sure printf outputs its buffer
      sleep(1);
    pthread_mutex_unlock(&mymutex);
    
    
    printf("o");
    fflush(stdout);
    sleep(1);
  }

  if ( pthread_join ( mythread, NULL )){
	printf("error joining thread."); abort();
  }
  printf("\nmyglobal equals %d\n",myglobal);
  exit(0);
}
