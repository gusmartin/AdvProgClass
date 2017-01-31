/**
 * Copyright (c) 2015 Abelardo López Lagunas
 *
 * @file    2_Space.c
 *
 * @author  Abelardo López Lagunas
 *
 * @date    Tue 29 Mar 2016 11:46 CST
 *
 * @brief   Shows how to share information between threads
 *
 * References:
 *          Have no idea where the original code came from, but it
 *          has been heavily modified to show the effects of stack
 *          vs heap memory allocation when using threads.
 *
 * Restrictions:
 *          There is no validation in the code
 *
 * Revision history:
 *          Tue 29 Mar 2016 11:46 CST -- File modified for conditional
 *          compilation also added some comments.
 *
 * @note    Used for the TC2025 class
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>                     // For the sleep function
#include <pthread.h>                    // For thread management

/* This is the basic data structure to be shared among threads */
struct foo {
       int a, b, c, d;
       };

/* This is a function that prints the elements of the structure above */
void printfoo(const char *s, const struct foo *fp)
{
     printf("%s", s);
     printf("  structure at 0x%lx\n", (unsigned long)fp);
     printf("  foo.a = %d\n", fp->a);
     printf("  foo.b = %d\n", fp->b);
     printf("  foo.c = %d\n", fp->c);
     printf("  foo.d = %d\n", fp->d);
}

/*
 * First thread function, note the conditional compilation to switch
 * between a Stack and Heap allocations.
 */
void * thr_fn1(void *arg)
{
  /* Switch between Stack and Heap allocations */
#ifdef STACK
   struct foo  foo = {1, 2, 3, 4};  // Stack allocation
   foo.a = 1;
   foo.b = 2;
   foo.c = 3;
   foo.d = 4;

   printfoo("thread 1:\n", &foo);  // Use with local struct
   pthread_exit((void *)&foo);     // Use with local struct

#else
  struct foo *foo = malloc (4*sizeof(int));
  foo->a = 1;
  foo->b = 2;
  foo->c = 3;
  foo->d = 4;

  printfoo("thread 1:\n", foo);  // Use with malloc (heap)
  pthread_exit((void *)foo);     // Use with malloc (heap)
#endif

}

/* Second thread function, just print its id */
void * thr_fn2(void *arg)
{
     printf("thread 2: ID is %lu\n", (unsigned long)pthread_self());
     pthread_exit((void *)0);
}

/* Main entry point */
int main(void)
{
    pthread_t   tid1, tid2;
    struct foo  *fp;

    if (pthread_create(&tid1, NULL, thr_fn1, NULL) != 0)
       perror("can’t create thread 1");

    if (pthread_join(tid1, (void *)&fp) != 0)
        perror("can’t join with thread 1");

    sleep(1);

    printf("parent starting second thread\n");

    if (pthread_create(&tid2, NULL, thr_fn2, NULL) != 0)
        perror("can’t create thread 2");

    sleep(1);

    printfoo("parent:\n", fp);

#ifndef STACK
    free (fp);
#endif

    return EXIT_SUCCESS;
}
