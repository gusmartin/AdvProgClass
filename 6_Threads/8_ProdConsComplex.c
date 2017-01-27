/**
 * Copyright (c) 2015 Abelardo López Lagunas
 *
 * @file    ProdConsComplex.c
 *
 * @author  Abelardo López Lagunas
 *
 * @date    Wed Mar 30 15:34:04 CST 2016
 *
 * @brief   Shows how to implement the Producer-Consumer model of
 *          communication between multiple producer and consumer threads.
 *
 * References:
 *          Derived from ProdCons.c which is the basic solution for
 *          the Producer - Consumer problem.
 *
 * Revision history:
 *          Wed Mar 30 15:34:04 CST 2016 -- File created and modified for
 *                  comments and general cleanup.
 *
 *          Fri Apr 01 10:54:27 CST 2016 -- Fixed syn bug on the consumer
 *                  a signal must be sent if it reads the LIMIT data.
 *
 * @note    Use for the TC2025 class
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>                 // For thread management
#include <unistd.h>                  // For the sleep function
#include <time.h>                    // Used to get the current time

#define BUFFER_SIZE 4
#define LIMIT     (-1)
#define COUNT      12

/*
 * Encapsulate the buffer with the mutex and conditional variables
 * so its easier to extend to multiple consumers/producers. Note that
 * the use of a circular buffer and that there is ONE instance of the
 * data structure defined as a global variable.
 */
struct prodcons {
  int buffer[BUFFER_SIZE];   /* Data to store */
  pthread_mutex_t key;       /* Synchronization variable */
  int read, write;           /* Read/Write position */
  pthread_cond_t notEmpty;   /* Signal buffer NOT empty */
  pthread_cond_t notFull;    /* Signal buffer NOT full */
} buffer;

/* This function initializes the shared data structure */
void init(struct prodcons * b)
{
  pthread_mutex_init(&b->key, NULL);
  pthread_cond_init(&b->notEmpty, NULL);
  pthread_cond_init(&b->notFull, NULL);
  b->read = 0;
  b->write = 0;
}

/* This function stores a data item in the buffer */
void Store(struct prodcons * b, int data)
{
  pthread_mutex_lock(&b->key);
  /* Wait until the buffer is not full */
  while ((b->write + 1) % BUFFER_SIZE == b->read) {
    pthread_cond_wait(&b->notFull, &b->key);
  }
  /*
   * This function suspends the thread until notFull is true
   * note that it will acquire the key when the thread resumes
   */
  b->buffer[b->write] = data;
  b->write++;
  if (b->write >= BUFFER_SIZE) b->write = 0;
  /* Signal buffer not full */
  pthread_cond_signal(&b->notEmpty);
  pthread_mutex_unlock(&b->key);
}

/* This function reads and removes a data item from the buffer */
int Get (struct prodcons * b)
{
  int data;
  pthread_mutex_lock(&b->key);
  /* Wait until the buffer is not empty */
  while (b->write == b->read) {
    pthread_cond_wait(&b->notEmpty, &b->key);
  }
  /*
   * This function suspends the thread until notEmpty is true
   * it also acquires the key when the thread resumes. Read
   * the data item and advance the pointer.
   */
  data = b->buffer[b->read];
  /*
   * More than one consumer is here so if we have reached the
   * limt do not advance the read pointer.
   */
  if (data != LIMIT){
	b->read++;
  } else {
      /* Make sure there reader gets a not-empty signal*/
      pthread_cond_signal(&b->notEmpty);
  }

  if (b->read >= BUFFER_SIZE) b->read = 0;
  /* Signal buffer not full */
  pthread_cond_signal(&b->notFull);
  pthread_mutex_unlock(&b->key);
  return (data);
}

/* This function produces COUNT elements and inserts them into the
 * shared data structure by calling Store().
 *
 * Note that there is only one producer so the name parameter is
 * not used.
 */
void * Producer(void *name)
{
  int n;
  int myNum = *((int*)name);   // Get the name (in case of N producers)

  for (n = 0; n < COUNT; n++) {
    printf("P %d ---> %d\n", myNum, n);
    Store(&buffer, n);          /* Insert an element */
    sleep(rand() % BUFFER_SIZE);
  }
  Store(&buffer, LIMIT);        /* Indicates the last element */

  return (NULL);
}

/* This function consumes elements and deletes them from the shared data
 * structure by calling Get() until the end of stream (LIMIT) value is read.
 *
 * The name is used to identify between both consumers.
 */
void * Consumer(void *name)
{
  int d;
  int myNum = *((int*)name);

  while (1) {
    d = Get(&buffer);
    if (d == LIMIT) break;
    printf("C %d ---> %d\n", myNum, d);
    sleep(rand() % BUFFER_SIZE);
  }
  return (NULL);
}

/* The main entry point, this follows the boss-worker model so the main
 * thread only creates the worker threads and then waits fro their
 * termination.
 */
int main(void)
{
  pthread_t th_a, th_b, th_c;   // Declare threads
  void * returnValue;           // Returned value from join function
  int th_name[3] = {0, 1, 2};   // Assign names to the threads

  init(&buffer);          // Initializes the shared structure

  srand (time(NULL));     // Use the current time as the seed

  /* Create the threads, One Producer, two Consumers */
  pthread_create(&th_a, NULL, Producer, &th_name[0]);
  pthread_create(&th_b, NULL, Consumer, &th_name[1]);
  pthread_create(&th_c, NULL, Consumer, &th_name[2]);

  /* Wait until all threads are done */
  pthread_join(th_a, &returnValue);
  printf("Prod\n");
  pthread_join(th_b, &returnValue);
    printf("C1\n");
  pthread_join(th_c, &returnValue);
   printf("C2\n");

  /* Not really needed but just show how conditionals and mutexes are
   * destroyed.
   */
  pthread_cond_destroy(&buffer.notEmpty);
  pthread_cond_destroy(&buffer.notFull);
  pthread_mutex_destroy(&buffer.key);

  return (0);             /* Tell the OS that there were no problems */
}
