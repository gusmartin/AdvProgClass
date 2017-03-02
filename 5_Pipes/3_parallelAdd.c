/**
 * @copyright (c) 2017 Abelardo López Lagunas
 *
 * @file    2_parallelAdd.c
 *
 * @author  Abelardo López Lagunas
 *
 * @date    Jan 20, 2017 09:31
 *
 * @brief   Shows how to use pipes with multiple processes
 *
 * References:
 *          Based on "A book on C" by Al Kelley & Ira Pohl
 *
 * Restrictions:
 *          If an error is found the program is aborted
 *
 * Revision history:
 *          Jan 20, 2017 09:32 -- File created
 *
 * @note    Meant as an example for the TC2025 students
 *
 */

#include <stdio.h>                     // printf, exit, exit values
#include <stdlib.h>                    // For exit conditions
#include <unistd.h>                    // For pipe constants

/* Controls the concurrency of the program*/
#define N 3         // Use this instead of a const to avoid a warning

/* Declares the function prototypes */
int  addVector(int v[], int length);

int main (void){

  int   array[N][N] = {{1, 1, 1},
		       {2, 2, 2},
		       {3, 3, 3}};
  int   i, row, sum = 0;
  int   pipefd[2];

  /* Create a simple pipe */
  if (pipe (pipefd) < 0){
	perror("Error creating the pipe");
  }
  
  /*
   * Create N child processes, each adds a row of the matrix
   * Note how the parent loops three times but does nothing.
   */
  for (i = 0; i < N; i++){
	if (fork() == 0) {
	  row = addVector(array[i], N);
	  
	  if (write (pipefd[1], &row, sizeof(int)) == -1)
	    perror("Error writing the pipe");
	  else
	    printf ("Child process %d finished working\n", getpid());

	  return (EXIT_SUCCESS);  /* child is done, terminate*/
	} else {
	  /*
	   * This is the parent process, it suspends if the data is not
	   * ready for consumption in the pipe. Parent collects partial
	   * sums and generates the total.
	   */
	  if (read (pipefd[0], &row, sizeof(int)) == -1)
	    perror("Error reading the pipe");
	  else
	    printf ("Parent read %d\n", row);
	  sum += row;
	}
  }

  printf ("The total is %d\n", sum);
  return (EXIT_SUCCESS);
}

/*
 *
 *  Function: addVector
 *
 *  Purpose:  This functions receives an array and its length as
 *            inputs and adds all its elements
 *
 *  Parameters:
 *            input #1  Pointer to the array
 *            input #2  Array length
 *            output    Sum of all array elements
 *
 */
int  addVector(int v[], int length){

  int i, sum;

  for (i = 0, sum = 0; i < length; i++)
	sum += v[i];

  sleep (random()%4);

  return (sum);
}
