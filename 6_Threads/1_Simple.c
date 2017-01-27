/**
 * Copyright (c) 2015 Abelardo López Lagunas
 *
 * @file    1_Simple.c
 *
 * @author  Abelardo López Lagunas
 *
 * @date    Tue 29 Mar 2016 11:33 CST
 *
 * @brief   Shows how to create and then join threads
 *
 * References:
 *          The code is based on the Intel class of 2006, but has
 *          been significantly modified.
 *
 * Restrictions:
 *          There is little or no validation in the code.
 *
 * Revision history:
 *          Tue 29 Mar 2016 11:33 CST -- File created
 *
 * @note    For the TC2025 class
 *
 */
#include <stdio.h>
#include <stdlib.h>                 // Used for sleep and rand
#include <time.h>                   // Used to get the current time
#include <unistd.h>                 // Used for getpid
#include <pthread.h>                // for thread management

void MyThread (void * arg){

  /*
   * Note that printing the thread requires an unsigned long int
   * unsigned long integer since that is the type of pthread_t
   * which is returned by pthread_self()
   */
  for (int i= 0; i < 5; i++){
	printf ("Thread: %s  i=%d pid is %d self is %u\n",(char *) arg,
		i, getpid(), (unsigned int) pthread_self());
	sleep (rand()%4);
  }
}

int main(void){

  int       code;             // Return code from the function
  pthread_t th_a, th_b;       // Define threads a & b


  srand (time(NULL));         // Use the current time as the seed

  /* Create two threads and pass a string as the name for each of
   * them. Note the typecasting to void *
   */
  code = pthread_create(&th_a, NULL,(void *) MyThread, (void *)"a");
  if (code != 0)
    printf("Failure when creating thread a %d\n", code);
  code = pthread_create(&th_b, NULL,(void *) MyThread, (void *)"b");
  if (code != 0)
    printf("Failure when creating thread b %d\n", code);

  /*
   * Main could behave as another thread, for now simply wait
   * until threads a and b finish
   */

  code = pthread_join(th_a, NULL);   /* Wait for thread a */
  if (code != 0)
    printf("Failure joining thread a %d\n", code);

  code = pthread_join(th_b, NULL);   /* Wait for thread b */
  if (code != 0)
    printf("Failure joining thread b %d\n", code);

  return 0;
 }
